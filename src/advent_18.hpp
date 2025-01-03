#ifndef ADVENT_18_HPP
#define ADVENT_18_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
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

    bool isInside(const Vec &f_pos) const
    {
        return (f_pos.row >= 0) && (f_pos.row < size.row) && (f_pos.col >= 0) && (f_pos.col < size.col);
    }

    void print()
    {
        for (auto &l_row : cells)
        {
            for (T l_cell : l_row)
            {
                std::cout << l_cell << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

typedef Grid<char> CharGrid;

struct Node
{
    Vec pos;
    uint64_t score;

    Node() {}
    Node(const Vec &f_pos, const uint64_t f_score)
        : pos(f_pos), score(f_score)
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
        size_t h1 = std::hash<int>{}(f_node.pos.row);
        size_t h2 = std::hash<int>{}(f_node.pos.col);
        return h1 ^ (h2 << 1);
    }
};

typedef std::unordered_map<Vec, Node, VecHash> NodeMap;

class Advent18
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    std::string solvePartTwo(const std::string &f_inputPath);

private:
    int readBlocks(const std::string &f_filePath, std::vector<Vec> &f_outBlocks) const;
    void setBlocksOnGrid(CharGrid &f_grid, const std::vector<Vec> &f_blocks) const;
    uint64_t findMinSteps(CharGrid &f_grid) const;
    Vec findLowestScoreNodePos(const NodeMap &f_nodeMap) const;
    void updateNeighborsScore(const Node f_parent, const CharGrid &f_grid, NodeMap &f_nodeMap) const;
    Vec findFirstBlockinBlock(const std::vector<Vec> &f_blocks) const;
};

#endif