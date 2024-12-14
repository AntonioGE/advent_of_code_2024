#ifndef ADVENT_14_HPP
#define ADVENT_14_HPP

#include <string>
#include <vector>
#include <cstdint>

struct Vec
{
    int row;
    int col;

    bool operator==(const Vec &other) const
    {
        return (row == other.row) && (col == other.col);
    }
};

struct VecHash
{
    size_t operator()(const Vec &v) const
    {
        size_t h1 = std::hash<int>{}(v.row);
        size_t h2 = std::hash<int>{}(v.col);
        return h1 ^ (h2 << 1);
    }
};

struct Robot
{
    Vec pos;
    Vec vel;
};

class Advent14
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readRobots(const std::string &f_filePath, std::vector<Robot> &f_outRobots) const;
    void moveRobots(std::vector<Robot> &f_robots, const Vec &f_mapSize, const int f_seconds) const;
    int wrapCoord(const int f_coord, const int f_mapSize) const;
    uint64_t getSafetyFactor(const std::vector<Robot> &f_robots, const Vec &f_mapSize) const;
    int getQuadrantCoord(const int f_coord, const int f_mapSize) const;
    bool areAllRobotsAlone(const std::vector<Robot> &f_robots) const;
    void printRobots(const std::vector<Robot> &f_robots, const Vec &f_mapSize) const;
};

#endif