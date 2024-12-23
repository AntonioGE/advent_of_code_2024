#ifndef ADVENT_16_HPP
#define ADVENT_16_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <iostream>

struct Vec
{
    int row;
    int col;

    bool operator==(const Vec &f_other) const
    {
        return (row == f_other.row) && (col == f_other.col);
    }

    bool operator!=(const Vec &f_other) const
    {
        return (row != f_other.row) || (col != f_other.col);
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

struct VecHash
{
    size_t operator()(const Vec &f_vec) const
    {
        size_t h1 = std::hash<int>{}(f_vec.row);
        size_t h2 = std::hash<int>{}(f_vec.col);
        return h1 ^ (h2 << 1);
    }
};

struct Pose
{
    Vec pos;
    int dirIdx;

    Pose() {}
    Pose(const Vec &f_pos, const int f_dirIdx) : pos(f_pos), dirIdx(f_dirIdx) {}
};

template <typename T>
struct Grid
{
    std::vector<std::vector<T>> cells;
    Vec size;

    Grid() : size{0, 0} {}

    Grid(int f_rows, int f_cols, const T &f_value)
    {
        cells.resize(f_rows);
        for (auto &l_row : cells)
        {
            l_row.resize(f_cols, f_value);
        }
        size.row = f_rows;
        size.col = f_cols;
    }

    T operator()(const int f_row, const int f_col) const
    {
        return cells[f_row][f_col];
    }

    T &operator()(const int f_row, const int f_col)
    {
        return cells[f_row][f_col];
    }

    T operator()(const Vec &f_pos) const
    {
        return cells[f_pos.row][f_pos.col];
    }

    T &operator()(const Vec &f_pos)
    {
        return cells[f_pos.row][f_pos.col];
    }

    void print()
    {
        for(auto &l_row : cells)
        {
            for(T l_cell : l_row)
            {
                std::cout << l_cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }   
};

struct Node
{
    Pose pose;
    uint64_t score;

    Node() {}
    Node(const Pose &f_pose, const uint64_t f_score)
        : pose(f_pose), score(f_score)
    {
    }
};

struct NodeCompare
{
    bool operator()(const Node &f_a, const Node &f_b)
    {
        return f_a.score > f_b.score;
    }
};

struct NodeHash
{
    size_t operator()(const Node &f_node) const
    {
        size_t h1 = std::hash<int>{}(f_node.pose.pos.row);
        size_t h2 = std::hash<int>{}(f_node.pose.pos.col);
        return h1 ^ (h2 << 1);
    }
};

typedef std::unordered_map<Vec, Node, VecHash> NodeMap;
typedef Grid<char> CharGrid;
typedef Grid<Node> NodeGrid;

class Advent16
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readGrid(const std::string &f_filePath, CharGrid &f_outMap) const;
    uint64_t findLowestScore(CharGrid &f_grid) const;
    Vec findInGrid(const CharGrid &f_grid, const char f_char) const;
    Vec findLowestScoreNodePos(const NodeMap &f_nodeMap) const;
    void updateNeighborsScore(const Node f_parent, const CharGrid &f_grid, NodeMap &f_nodeMap) const;
};

#endif