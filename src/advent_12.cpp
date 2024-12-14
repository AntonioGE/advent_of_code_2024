#include "advent_12.hpp"

#include <iostream>
#include <fstream>

#include "advent_common.hpp"

const Vec g_dirTable[4] = {
    Vec{0, -1},
    Vec{0, 1},
    Vec{-1, 0},
    Vec{1, 0}};

int main()
{
    AdventCommon::printDay(12);

    Advent12 l_advent12;
    std::cout << "Result Part One: " << l_advent12.solvePartOne("res/input_12.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent12.solvePartTwo("res/input_12.txt") << std::endl;

    return 0;
}

uint64_t Advent12::solvePartOne(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return getPriceSum(l_map);
}

uint64_t Advent12::solvePartTwo(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return getDiscountPriceSum(l_map);
}

int Advent12::readMap(const std::string &f_filePath, Map &f_outMap) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outMap.cells.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.empty())
        {
            continue;
        }

        std::vector<char> l_charLine(l_line.begin(), l_line.end());
        f_outMap.cells.push_back(l_charLine);
    }

    f_outMap.rows = f_outMap.cells.size();
    f_outMap.cols = f_outMap.cells.empty() ? 0 : f_outMap.cells[0].size();

    l_file.close();

    return 0; // Success
}

uint64_t Advent12::getPriceSum(const Map &f_map) const
{
    uint64_t l_sum = 0;

    Map l_checkedMap(f_map.rows, f_map.cols, 0);
    for (int i = 0; i < f_map.rows; i++)
    {
        for (int j = 0; j < f_map.cols; j++)
        {
            if (!l_checkedMap(i, j))
            {
                Region l_region{0, 0};
                growRegion(f_map, Vec{i, j}, l_checkedMap, l_region);
                l_sum += l_region.area * l_region.perimeter;
            }
        }
    }

    return l_sum;
}

void Advent12::growRegion(const Map &f_map, const Vec &f_pos, Map &f_checkedMap, Region &f_region) const
{
    f_region.area++;
    f_checkedMap(f_pos) = 1;

    const char l_flower = f_map(f_pos);
    for (int i = 0; i < 4; i++)
    {
        const Vec &l_dir = g_dirTable[i];
        Vec l_next = f_pos + l_dir;
        if (isInsideMap(f_map, l_next) && (f_map(l_next) == l_flower))
        {
            if (!f_checkedMap(l_next))
            {
                growRegion(f_map, l_next, f_checkedMap, f_region);
            }
        }
        else
        {
            f_region.perimeter++;
        }
    }
}

bool Advent12::isInsideMap(const Map &f_map, const Vec &f_pos) const
{
    return (f_pos.row >= 0) && (f_pos.row < f_map.rows) && (f_pos.col >= 0) && (f_pos.col < f_map.cols);
}

uint64_t Advent12::getDiscountPriceSum(const Map &f_map) const
{
    uint64_t l_sum = 0;

    Map l_checkedMap(f_map.rows, f_map.cols, 0);
    FenceMap l_fenceMap;
    l_fenceMap.h = Map(f_map.rows + 1, f_map.cols, 0);
    l_fenceMap.v = Map(f_map.rows, f_map.cols + 1, 0);
    for (int i = 0; i < f_map.rows; i++)
    {
        for (int j = 0; j < f_map.cols; j++)
        {
            if (!l_checkedMap(i, j))
            {
                l_fenceMap.h.fill(0);
                l_fenceMap.v.fill(0);
                uint64_t l_area = 0;
                growDiscountRegion(f_map, Vec{i, j}, l_checkedMap, l_fenceMap, l_area);

                int l_fences = countFences(l_fenceMap);

                l_sum += l_area * l_fences;
            }
        }
    }

    return l_sum;
}

void Advent12::growDiscountRegion(const Map &f_map, const Vec &f_pos, Map &f_checkedMap, FenceMap &f_fenceMap, uint64_t &f_area) const
{
    f_area++;
    f_checkedMap(f_pos) = 1;

    const char l_flower = f_map(f_pos);
    for (int i = 0; i < 4; i++)
    {
        const Vec &l_dir = g_dirTable[i];
        Vec l_next = f_pos + l_dir;
        if (isInsideMap(f_map, l_next) && (f_map(l_next) == l_flower))
        {
            if (!f_checkedMap(l_next))
            {
                growDiscountRegion(f_map, l_next, f_checkedMap, f_fenceMap, f_area);
            }
        }
        else
        {
            if (i < 2)
            {
                f_fenceMap.v(f_pos.row, f_pos.col + (i % 2)) = 1;
            }
            else
            {
                f_fenceMap.h(f_pos.row + (i % 2), f_pos.col) = 1;
            }
        }
    }
}

int Advent12::countFences(const FenceMap &f_fenceMap) const
{
    int l_countH = 0;

    for (int i = 0; i < f_fenceMap.h.rows; i++)
    {
        bool l_onFence = false;
        for (int j = 0; j < f_fenceMap.h.cols; j++)
        {
            if (f_fenceMap.h(i, j))
            {
                if ((!l_onFence) || (l_onFence && (i < f_fenceMap.v.rows) && f_fenceMap.v(i, j) && f_fenceMap.v(i - 1, j)))
                {
                    l_countH++;
                    l_onFence = true;
                }
            }
            else
            {
                l_onFence = false;
            }
        }
    }

    int l_countV = 0;

    for (int i = 0; i < f_fenceMap.v.cols; i++)
    {
        bool l_onFence = false;
        for (int j = 0; j < f_fenceMap.v.rows; j++)
        {
            if (f_fenceMap.v(j, i))
            {
                if ((!l_onFence) || (l_onFence && (i < f_fenceMap.h.cols) && f_fenceMap.h(j, i) && f_fenceMap.h(j, i - 1)))
                {
                    l_countV++;
                    l_onFence = true;
                }
            }
            else
            {
                l_onFence = false;
            }
        }
    }

    return l_countH + l_countV;
}
