#include "advent_6.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>

#include "advent_common.hpp"

const Vec Pose::g_dirTable[4] = {
    Vec{-1, 0},
    Vec{0, 1},
    Vec{1, 0},
    Vec{0, -1}};

int main()
{
    AdventCommon::printDay(6);

    Advent6 l_advent6;
    std::cout << "Result Part One: " << l_advent6.solvePartOne("res/input_6.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent6.solvePartTwo("res/input_6.txt") << std::endl;

    return 0;
}

int Advent6::solvePartOne(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return countDistinctPositions(l_map);
}

int Advent6::solvePartTwo(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return countObsctructionPoints(l_map);
}

int Advent6::readMap(const std::string &f_filePath, Map &f_outMap) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outMap.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        std::vector<char> l_charLine(l_line.begin(), l_line.end());
        f_outMap.push_back(l_charLine);
    }

    l_file.close();

    return 0; // Success
}

int Advent6::countDistinctPositions(Map &f_map) const
{
    int l_count = 0;

    Pose l_pose = findInitPose(f_map);
    while (isInsideMap(f_map, l_pose.pos))
    {
        if (getMapCell(f_map, l_pose.pos) != 'X')
        {
            setMapCell(f_map, l_pose.pos, 'X');
            l_count++;
        }
        l_pose = getNextPose(f_map, l_pose);
    }

    return l_count;
}

char Advent6::getMapCell(const Map &f_map, const Vec f_pos) const
{
    return f_map[f_pos.row][f_pos.col];
}

void Advent6::setMapCell(Map &f_map, const Vec f_pos, const char f_cell) const
{
    f_map[f_pos.row][f_pos.col] = f_cell;
}

Pose Advent6::findInitPose(const Map &f_map) const
{
    for (int i = 0; i < f_map.size(); i++)
    {
        for (int j = 0; j < f_map[i].size(); j++)
        {
            if (f_map[i][j] == '^')
            {
                return Pose{Vec{i, j}, 0};
            }
        }
    }

    return Pose{Vec{-1, -1}, 0};
}

Pose Advent6::getNextPose(const Map &f_map, const Pose &f_pose) const
{
    Pose l_next = f_pose;
    while (hasCollisionFront(f_map, l_next))
    {
        rotatePose(l_next);
    }

    l_next.pos = l_next.pos + l_next.getDir();

    return l_next;
}

bool Advent6::hasCollisionFront(const Map &f_map, const Pose &f_pose) const
{
    Vec l_pos = f_pose.pos + f_pose.getDir();
    return isInsideMap(f_map, l_pos) && (getMapCell(f_map, l_pos) == '#');
}

bool Advent6::isInsideMap(const Map &f_map, const Vec &f_pos) const
{
    return (f_pos.row >= 0) && (f_pos.row < f_map.size()) && (f_pos.col >= 0) && (f_pos.col < f_map[0].size());
}

void Advent6::rotatePose(Pose &f_pose) const
{
    f_pose.dirIdx = (f_pose.dirIdx + 1) % 4;
}

int Advent6::countObsctructionPoints(const Map &f_map) const
{
    int l_count = 0;

    Pose l_pose = findInitPose(f_map);
    for (int i = 0; i < f_map.size(); i++)
    {
        for (int j = 0; j < f_map[i].size(); j++)
        {
            if (isObstructionPoint(f_map, l_pose, Vec{i, j}))
            {
                l_count++;
            }
        }
    }

    return l_count;
}

bool Advent6::isObstructionPoint(Map f_map, const Pose &f_initPose, const Vec f_obstrPos) const
{
    if (getMapCell(f_map, f_obstrPos) != '.')
    {
        return false;
    }

    Pose l_pose = f_initPose;
    setMapCell(f_map, f_initPose.pos, '.');
    setMapCell(f_map, f_obstrPos, '#');
    while (isInsideMap(f_map, l_pose.pos))
    {
        char l_cell = getMapCell(f_map, l_pose.pos);
        if (l_cell == '.')
        {
            setMapCell(f_map, l_pose.pos, l_pose.dirIdx);
        }
        else if (l_cell == l_pose.dirIdx)
        {
            return true; // Revisited position with same direction as before
        }
        l_pose = getNextPose(f_map, l_pose);
    }

    return false;
}
