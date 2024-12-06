#ifndef ADVENT_5_HPP
#define ADVENT_5_HPP

#include <string>
#include <vector>

typedef std::vector<std::vector<char>> Map;

struct Vec
{
    int row;
    int col;

    inline friend Vec operator+(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row + f_rhs.row, f_lhs.col + f_rhs.col};
    }
};

struct Pose
{
    static const Vec g_dirTable[4];

    Vec pos;
    int dirIdx;

    inline const Vec &getDir() const
    {
        return g_dirTable[dirIdx];
    }
};

class Advent6
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readMap(const std::string &f_filePath, Map &f_outMap) const;
    int countDistinctPositions(Map &f_map) const;
    char getMapCell(const Map &f_map, const Vec f_pos) const;
    void setMapCell(Map &f_map, const Vec f_pos, const char f_cell) const;
    Pose findInitPose(const Map &f_map) const;
    Pose getNextPose(const Map &f_map, const Pose &f_pose) const;
    bool hasCollisionFront(const Map &f_map, const Pose &f_pose) const;
    bool isInsideMap(const Map &f_map, const Vec &f_pos) const;
    void rotatePose(Pose &f_pose) const;
    int countObsctructionPoints(const Map &f_map) const;
    bool isObstructionPoint(Map f_map, const Pose &f_initPose, const Vec f_obstrPos) const;
};

#endif