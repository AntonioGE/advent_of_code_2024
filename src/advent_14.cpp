#include "advent_14.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(14);

    Advent14 l_advent14;
    std::cout << "Result Part One: " << l_advent14.solvePartOne("res/input_14.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent14.solvePartTwo("res/input_14.txt") << std::endl;

    return 0;
}

uint64_t Advent14::solvePartOne(const std::string &f_inputPath)
{
    std::vector<Robot> l_robots;
    if (readRobots(f_inputPath, l_robots) != 0)
    {
        return -1;
    }

    Vec l_mapSize{103, 101};
    moveRobots(l_robots, l_mapSize, 100);
    return getSafetyFactor(l_robots, l_mapSize);
}

uint64_t Advent14::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<Robot> l_robots;
    if (readRobots(f_inputPath, l_robots) != 0)
    {
        return -1;
    }

    Vec l_mapSize{103, 101};
    int l_seconds = 0;
    while (!areAllRobotsAlone(l_robots))
    {
        moveRobots(l_robots, l_mapSize, 1);
        l_seconds++;
    }
    return l_seconds;
}

int Advent14::readRobots(const std::string &f_filePath, std::vector<Robot> &f_outRobots) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outRobots.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        Robot l_robot;
        int l_n = sscanf(l_line.c_str(), "p=%d,%d v=%d,%d", &l_robot.pos.col, &l_robot.pos.row, &l_robot.vel.col, &l_robot.vel.row);
        if (l_n == 4)
        {
            f_outRobots.push_back(l_robot);
        }
    }

    l_file.close();

    return 0; // Success
}

void Advent14::moveRobots(std::vector<Robot> &f_robots, const Vec &f_mapSize, const int f_seconds) const
{
    for (Robot &l_robot : f_robots)
    {
        l_robot.pos.row = wrapCoord(l_robot.pos.row + l_robot.vel.row * f_seconds, f_mapSize.row);
        l_robot.pos.col = wrapCoord(l_robot.pos.col + l_robot.vel.col * f_seconds, f_mapSize.col);
    }
}

int Advent14::wrapCoord(const int f_coord, const int f_mapSize) const
{
    return ((f_coord % f_mapSize) + f_mapSize) % f_mapSize;
}

uint64_t Advent14::getSafetyFactor(const std::vector<Robot> &f_robots, const Vec &f_mapSize) const
{
    int l_quadrants[2][2] = {0};
    for (const Robot &l_robot : f_robots)
    {
        int l_row = getQuadrantCoord(l_robot.pos.row, f_mapSize.row);
        int l_col = getQuadrantCoord(l_robot.pos.col, f_mapSize.col);
        if ((l_row != -1) && (l_col != -1))
        {
            l_quadrants[l_row][l_col]++;
        }
    }

    uint64_t l_safetyFactor = 1;
    for (int i = 0; i < 4; i++)
    {
        l_safetyFactor *= l_quadrants[i / 2][i % 2];
    }
    return l_safetyFactor;
}

int Advent14::getQuadrantCoord(const int f_coord, const int f_mapSize) const
{
    if (f_coord < (f_mapSize / 2))
    {
        return 0;
    }
    if (f_coord > (f_mapSize / 2))
    {
        return 1;
    }
    return -1;
}

bool Advent14::areAllRobotsAlone(const std::vector<Robot> &f_robots) const
{
    std::unordered_set<Vec, VecHash> l_usedPos;
    for (const Robot &l_robot : f_robots)
    {
        if (l_usedPos.find(l_robot.pos) == l_usedPos.end())
        {
            l_usedPos.insert(l_robot.pos);
        }
        else
        {
            return false;
        }
    }

    return true;
}

void Advent14::printRobots(const std::vector<Robot> &f_robots, const Vec &f_mapSize) const
{
    std::vector<int> l_map(f_mapSize.row * f_mapSize.col, 0);
    for (const Robot &l_robot : f_robots)
    {
        l_map[l_robot.pos.row * f_mapSize.col + l_robot.pos.col]++;
    }

    for (int i = 0; i < f_mapSize.row; i++)
    {
        for (int j = 0; j < f_mapSize.col; j++)
        {
            std::cout << l_map[i * f_mapSize.col + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
