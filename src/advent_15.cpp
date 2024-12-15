#include "advent_15.hpp"

#include <iostream>
#include <fstream>
#include <vector>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(15);

    Advent15 l_advent15;
    std::cout << "Result Part One: " << l_advent15.solvePartOne("res/input_15.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent15.solvePartTwo("res/input_15.txt") << std::endl;

    return 0;
}

uint64_t Advent15::solvePartOne(const std::string &f_inputPath)
{
    Map l_map;
    std::vector<Vec> l_moves;
    if (readMapAndMoves(f_inputPath, l_map, l_moves) != 0)
    {
        return -1;
    }

    return moveAndSumBoxes(l_map, l_moves);
}

uint64_t Advent15::solvePartTwo(const std::string &f_inputPath)
{
    Map l_map;
    std::vector<Vec> l_moves;
    if (readMapAndMoves(f_inputPath, l_map, l_moves) != 0)
    {
        return -1;
    }

    return moveAndSumBoxesExpanded(l_map, l_moves);
}

uint64_t Advent15::moveAndSumBoxes(Map &f_map, std::vector<Vec> &f_moves) const
{
    Vec l_robot = findRobot(f_map);
    for (const Vec &l_move : f_moves)
    {
        moveRobot(f_map, l_robot, l_move);
    }

    return sumBoxesGPS(f_map);
}

int Advent15::readMapAndMoves(const std::string &f_filePath, Map &f_outMap, std::vector<Vec> &f_outMoves) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outMoves.clear();

    bool l_readMap = true;
    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.empty())
        {
            l_readMap = false;
        }

        if (l_readMap)
        {
            std::vector<char> l_charLine(l_line.begin(), l_line.end());
            f_outMap.cells.push_back(l_charLine);
        }
        else
        {
            for (const char l_char : l_line)
            {
                switch (l_char)
                {
                case '^':
                {
                    f_outMoves.push_back(Vec{-1, 0});
                    break;
                }
                case 'v':
                {
                    f_outMoves.push_back(Vec{1, 0});
                    break;
                }
                case '<':
                {
                    f_outMoves.push_back(Vec{0, -1});
                    break;
                }
                case '>':
                {
                    f_outMoves.push_back(Vec{0, 1});
                    break;
                }
                }
            }
        }
    }

    f_outMap.size.row = f_outMap.cells.size();
    if (!f_outMap.cells.empty())
    {
        f_outMap.size.col = f_outMap.cells[0].size();
    }

    l_file.close();

    return 0; // Success
}

Vec Advent15::findRobot(Map &f_map) const
{
    for (int i = 0; i < f_map.cells.size(); i++)
    {
        for (int j = 0; j < f_map.cells[i].size(); j++)
        {
            if (f_map(i, j) == '@')
            {
                f_map(i, j) = '.';
                return Vec{i, j};
            }
        }
    }

    return Vec{0, 0};
}

void Advent15::moveRobot(Map &f_map, Vec &f_robot, const Vec &f_move) const
{
    Vec l_newPos = f_robot + f_move;

    if (f_map(l_newPos) == '.')
    {
        f_robot = l_newPos;
    }
    else if (f_map(l_newPos) == 'O')
    {
        Vec l_boxPos = l_newPos;
        while (f_map(l_boxPos) == 'O')
        {
            l_boxPos = l_boxPos + f_move;
        }

        if (f_map(l_boxPos) == '.')
        {
            f_map(l_boxPos) = 'O';
            f_map(l_newPos) = '.';
            f_robot = l_newPos;
        }
    }
}

uint64_t Advent15::sumBoxesGPS(const Map &f_map) const
{
    uint64_t l_sum = 0;
    for (int i = 0; i < f_map.cells.size(); i++)
    {
        for (int j = 0; j < f_map.cells[i].size(); j++)
        {
            if (f_map(i, j) == 'O')
            {
                l_sum += 100 * i + j;
            }
        }
    }
    return l_sum;
}

Map Advent15::expandMap(const Map &f_map) const
{
    Map l_copy;
    l_copy.cells.resize(f_map.cells.size());

    for (int i = 0; i < f_map.cells.size(); i++)
    {
        l_copy.cells[i].resize(2 * f_map.cells[i].size());
        for (int j = 0; j < f_map.cells[i].size(); j++)
        {
            switch (f_map.cells[i][j])
            {
            case '#':
                l_copy.cells[i][j * 2 + 0] = '#';
                l_copy.cells[i][j * 2 + 1] = '#';
                break;
            case 'O':
                l_copy.cells[i][j * 2 + 0] = '[';
                l_copy.cells[i][j * 2 + 1] = ']';
                break;
            case '.':
                l_copy.cells[i][j * 2 + 0] = '.';
                l_copy.cells[i][j * 2 + 1] = '.';
                break;
            case '@':
                l_copy.cells[i][j * 2 + 0] = '@';
                l_copy.cells[i][j * 2 + 1] = '.';
                break;
            }
        }
    }

    l_copy.size.row = f_map.size.row;
    l_copy.size.col = f_map.size.col * 2;

    return l_copy;
}

uint64_t Advent15::moveAndSumBoxesExpanded(const Map &f_map, const std::vector<Vec> &f_moves) const
{
    Map l_expMap = expandMap(f_map);
    Vec l_robot = findRobot(l_expMap);

    // printMap(l_expMap, l_robot);

    for (const Vec &l_move : f_moves)
    {
        // std::cout << "Move: " << l_move.row << " " << l_move.col << std::endl;
        moveRobotExpanded(l_expMap, l_robot, l_move);
        // printMap(l_expMap, l_robot);
    }

    return sumExpBoxesGPS(l_expMap);
}

void Advent15::moveRobotExpanded(Map &f_map, Vec &f_robot, const Vec &f_move) const
{
    Vec l_newPos = f_robot + f_move;

    char l_nextCell = f_map(l_newPos);
    if (l_nextCell == '.')
    {
        f_robot = l_newPos;
    }
    else if (isExpandedBox(l_nextCell))
    {
        Vec l_boxPos = l_newPos;

        if (f_move.row == 0) // Horizontal movement
        {
            while (isExpandedBox(f_map(l_boxPos)))
            {
                l_boxPos = l_boxPos + f_move;
            }

            if (f_map(l_boxPos) == '.')
            {
                moveExpBoxesHorizontally(f_map, l_newPos, l_boxPos, f_move);
                f_robot = l_newPos;
            }
        }
        else // Vertical movement
        {
            if (canMoveExpBoxVertically(f_map, l_boxPos, f_move))
            {
                moveExpBoxVertically(f_map, l_boxPos, f_move);
                f_robot = l_newPos;
            }
        }
    }
}

bool Advent15::isExpandedBox(const char f_cell) const
{
    return (f_cell == '[') || (f_cell == ']');
}

void Advent15::moveExpBoxesHorizontally(Map &f_map, const Vec &f_begin, const Vec &f_end, const Vec &f_dir) const
{
    for (Vec l_pos = f_end; !(l_pos == f_begin); l_pos = l_pos - f_dir)
    {
        f_map(l_pos) = f_map(l_pos - f_dir);
    }
    f_map(f_begin) = '.';
}

bool Advent15::canMoveExpBoxVertically(const Map &f_map, const Vec &f_pos, const Vec &f_dir) const
{
    const ExpBox l_currBox = getExpBoxPositions(f_map, f_pos);

    for (int i = 0; i < 2; i++)
    {
        Vec l_nextPos = l_currBox.pos[i] + f_dir;
        char l_nextCell = f_map(l_nextPos);

        if (l_nextCell == '.')
        {
            continue;
        }
        else if (isExpandedBox(l_nextCell) && canMoveExpBoxVertically(f_map, l_nextPos, f_dir))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

ExpBox Advent15::getExpBoxPositions(const Map &f_map, const Vec &f_pos) const
{
    if (f_map(f_pos.row, f_pos.col) == '[')
    {
        return ExpBox{f_pos, f_pos + Vec{0, 1}};
    }
    else
    {
        return ExpBox{f_pos - Vec{0, 1}, f_pos};
    }
}

void Advent15::moveExpBoxVertically(Map &f_map, const Vec &f_pos, const Vec &f_dir) const
{
    const ExpBox l_currBox = getExpBoxPositions(f_map, f_pos);

    for (int i = 0; i < 2; i++)
    {
        Vec l_nextPos = l_currBox.pos[i] + f_dir;
        char l_nextCell = f_map(l_nextPos);

        if (isExpandedBox(l_nextCell))
        {
            moveExpBoxVertically(f_map, l_nextPos, f_dir);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        Vec l_nextPos = l_currBox.pos[i] + f_dir;
        f_map(l_nextPos) = f_map(l_currBox.pos[i]);
        f_map(l_currBox.pos[i]) = '.';
    }
}

uint64_t Advent15::sumExpBoxesGPS(const Map &f_map) const
{
    uint64_t l_sum = 0;
    for (int i = 0; i < f_map.cells.size(); i++)
    {
        for (int j = 0; j < f_map.cells[i].size(); j++)
        {
            if (f_map(i, j) == '[')
            {
                l_sum += 100 * i + j;
            }
        }
    }
    return l_sum;
}
