#ifndef ADVENT_12_HPP
#define ADVENT_12_HPP

#include <string>
#include <vector>
#include <cstdint>

struct Region
{
    uint64_t area;
    uint64_t perimeter;
};

struct Vec
{
    int row;
    int col;

    inline friend Vec operator+(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row + f_rhs.row, f_lhs.col + f_rhs.col};
    }
};

struct Map
{
    std::vector<std::vector<char>> cells;
    int rows;
    int cols;

    Map()
        : rows(0), cols(0)
    {
    }

    Map(const int f_rows, const int f_cols, const char f_value)
        : cells(f_rows), rows(f_rows), cols(f_cols)
    {
        for (int i = 0; i < rows; i++)
        {
            cells[i].resize(cols, f_value);
        }
    }

    void fill(const char f_value)
    {
        for (int i = 0; i < cells.size(); i++)
        {
            for (int j = 0; j < cells[i].size(); j++)
            {
                cells[i][j] = f_value;
            }
        }
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

struct FenceMap
{
    Map h;
    Map v;
};


class Advent12
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readMap(const std::string &f_filePath, Map &f_outMap) const;
    uint64_t getPriceSum(const Map &f_map) const;
    void growRegion(const Map &f_map, const Vec &f_pos, Map &f_checkedMap, Region &f_region) const;
    bool isInsideMap(const Map &f_map, const Vec &f_pos) const;
    uint64_t getDiscountPriceSum(const Map &f_map) const;
    Map getFenceMapH(const Map &f_map) const;
    void growDiscountRegion(const Map &f_map, const Vec &f_pos, Map &f_checkedMap, FenceMap &f_fenceMap, uint64_t &f_area) const;
    int countFences(const FenceMap &f_fenceMap) const;
};

#endif