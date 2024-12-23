#include "advent_16.hpp"

#include <iostream>
#include <fstream>

#include "advent_common.hpp"

Vec g_dirTable[4] = {
    Vec{0, 1},
    Vec{-1, 0},
    Vec{0, -1},
    Vec{1, 0}};

int g_scoreTable[4] = {
    1,
    1001,
    2001,
    1001};

char g_charDirTable[4] = {
    '>', 
    '^',
    '<',
    'v'
};

int main()
{
    AdventCommon::printDay(16);

    Advent16 l_advent16;
    std::cout << "Result Part One: " << l_advent16.solvePartOne("res/input_16.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent16.solvePartTwo("res/input_16.txt") << std::endl;

    return 0;
}

uint64_t Advent16::solvePartOne(const std::string &f_inputPath)
{
    CharGrid l_grid;
    if (readGrid(f_inputPath, l_grid) != 0)
    {
        return -1;
    }

    return findLowestScore(l_grid);
}

uint64_t Advent16::solvePartTwo(const std::string &f_inputPath)
{
    CharGrid l_grid;
    if (readGrid(f_inputPath, l_grid) != 0)
    {
        return -1;
    }

    return 0; //countBestCells(l_grid);
}

int Advent16::readGrid(const std::string &f_filePath, CharGrid &f_outGrid) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outGrid.cells.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.empty())
        {
            continue;
        }

        std::vector<char> l_charLine(l_line.begin(), l_line.end());
        f_outGrid.cells.push_back(l_charLine);
    }

    f_outGrid.size.row = f_outGrid.cells.size();
    f_outGrid.size.col = f_outGrid.cells.empty() ? 0 : f_outGrid.cells[0].size();

    l_file.close();

    return 0; // Success
}

uint64_t Advent16::findLowestScore(CharGrid &f_grid) const
{
    const Vec l_startPos = findInGrid(f_grid, 'S');
    const Node l_start(Pose(l_startPos, 0), 0);

    const Vec l_endPos = findInGrid(f_grid, 'E');
    f_grid(l_endPos) = '.';

    NodeMap l_nodeMapUnvisited;
    l_nodeMapUnvisited[l_start.pose.pos] = l_start;

    while (!l_nodeMapUnvisited.empty())
    {
        const Node &l_node = l_nodeMapUnvisited[findLowestScoreNodePos(l_nodeMapUnvisited)];

        if (l_node.pose.pos != l_endPos)
        {
            updateNeighborsScore(l_node, f_grid, l_nodeMapUnvisited);
            f_grid(l_node.pose.pos) = g_charDirTable[l_node.pose.dirIdx];
            l_nodeMapUnvisited.erase(l_node.pose.pos);
        }
        else
        {
            // f_grid.print();
            return l_node.score;
        }
    }

    return 0;
}

Vec Advent16::findInGrid(const CharGrid &f_grid, const char f_char) const
{
    for (int i = 0; i < f_grid.size.row; i++)
    {
        for (int j = 0; j < f_grid.size.col; j++)
        {
            if (f_grid(i, j) == f_char)
            {
                return Vec{i, j};
            }
        }
    }
    return Vec{0, 0};
}

Vec Advent16::findLowestScoreNodePos(const NodeMap &f_nodeMap) const
{
    Vec l_posMinNode{0, 0};
    uint64_t l_minScore = 0xFFFFFFFFFFFFFFFF;
    for (const auto &l_entry : f_nodeMap)
    {
        if (l_entry.second.score < l_minScore)
        {
            l_minScore = l_entry.second.score;
            l_posMinNode = l_entry.first;
        }
    }
    return l_posMinNode;
}

void Advent16::updateNeighborsScore(const Node f_parent, const CharGrid &f_grid, NodeMap &f_nodeMap) const
{
    for (int i = 0; i < 4; i++)
    {
        const int l_dirIdx = (f_parent.pose.dirIdx + i) % 4;
        const Vec l_pos = f_parent.pose.pos + g_dirTable[l_dirIdx];
        if (f_grid(l_pos) != '.')
        {
            continue;
        }

        const int l_score = f_parent.score + g_scoreTable[i];
        auto l_it = f_nodeMap.find(l_pos);
        if (l_it == f_nodeMap.end())
        {
            f_nodeMap[l_pos] = Node(Pose(l_pos, l_dirIdx), l_score);
        }
        else if(l_score < l_it->second.score)
        {
            Node &l_neighbor = l_it->second;
            l_neighbor.score = l_score;
            l_neighbor.pose.dirIdx = l_dirIdx;
        }
    }
}
