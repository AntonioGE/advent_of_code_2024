#ifndef ADVENT_15_HPP
#define ADVENT_15_HPP

#include <string>
#include <vector>
#include <cstdint>

struct Vec
{
    int row;
    int col;

    bool operator==(const Vec &f_other) const
    {
        return (row == f_other.row) && (col == f_other.col);
    }

    inline friend Vec operator+(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row + f_rhs.row, f_lhs.col + f_rhs.col};
    }

    inline friend Vec operator-(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row - f_rhs.row, f_lhs.col - f_rhs.col};
    }
};

struct Map
{
    std::vector<std::vector<char>> cells;
    Vec size;

    Map()
        : size{0, 0}
    {
    }

    char operator()(const int f_row, const int f_col) const
    {
        return cells[f_row][f_col];
    }

    char &operator()(const int f_row, const int f_col)
    {
        return cells[f_row][f_col];
    }

    char operator()(const Vec &f_pos) const
    {
        return cells[f_pos.row][f_pos.col];
    }

    char &operator()(const Vec &f_pos)
    {
        return cells[f_pos.row][f_pos.col];
    }
};

struct ExpBox
{
    Vec pos[2];
};

class Advent15
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readMapAndMoves(const std::string &f_filePath, Map &f_outMap, std::vector<Vec> &f_outMoves) const;
    uint64_t moveAndSumBoxes(Map &f_map, std::vector<Vec> &f_moves) const;
    Vec findRobot(Map &f_map) const;
    void moveRobot(Map &f_map, Vec &f_robot, const Vec &f_move) const;
    uint64_t sumBoxesGPS(const Map &f_map) const;
    uint64_t moveAndSumBoxesExpanded(const Map &f_map, const std::vector<Vec> &f_moves) const;
    Map expandMap(const Map &f_map) const;
    void moveRobotExpanded(Map &f_map, Vec &f_robot, const Vec &f_move) const;
    bool isExpandedBox(const char f_cell) const;
    void moveExpBoxesHorizontally(Map &f_map, const Vec &f_begin, const Vec &f_end, const Vec &f_dir) const;
    bool canMoveExpBoxVertically(const Map &f_map, const Vec &f_pos, const Vec &f_dir) const;
    ExpBox getExpBoxPositions(const Map &f_map, const Vec &f_pos) const;
    void moveExpBoxVertically(Map &f_map, const Vec &f_pos, const Vec &f_dir) const;
    uint64_t sumExpBoxesGPS(const Map &f_map) const;
};

#endif