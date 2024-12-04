#include "advent_4.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(4);

    Advent4 l_advent4;
    std::cout << "Result Part One: " << l_advent4.solvePartOne("res/input_4.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent4.solvePartTwo("res/input_4.txt") << std::endl;

    return 0;
}

int Advent4::solvePartOne(const std::string &f_inputPath)
{
    std::vector<std::vector<char>> l_mtx;
    if (readFileAsCharMtx(f_inputPath, l_mtx) != 0)
    {
        return -1;
    }

    return countXmas(l_mtx);
}

int Advent4::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<std::vector<char>> l_mtx;
    if (readFileAsCharMtx(f_inputPath, l_mtx) != 0)
    {
        return -1;
    }

    return countMasX(l_mtx);
}

int Advent4::readFileAsCharMtx(const std::string &f_filePath, std::vector<std::vector<char>> &f_outMtx) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outMtx.clear();
    std::string line;
    while (std::getline(l_file, line))
    {
        f_outMtx.push_back(std::vector<char>(line.begin(), line.end()));
    }

    l_file.close();
    return 0; // Success
}

int Advent4::countXmas(const std::vector<std::vector<char>> &f_mtx) const
{
    int l_count = 0;

    const int l_dirs[8][2] = {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}};

    for (int i = 0; i < f_mtx.size(); i++)
    {
        for (int j = 0; j < f_mtx[i].size(); j++)
        {
            for (int d = 0; d < 8; d++)
            {
                if (isXmasAtDir(f_mtx, i, j, l_dirs[d][0], l_dirs[d][1]))
                {
                    l_count++;
                }
            }
        }
    }

    return l_count;
}

bool Advent4::isXmasAtDir(const std::vector<std::vector<char>> &f_mtx, const int f_row, const int f_col, const int f_drow, const int f_dcol) const
{
    const int l_rows = f_mtx.size();
    const int l_cols = f_mtx[f_row].size();

    const char *l_xmas = "XMAS";
    for (int i = 0; i < 4; i++)
    {
        int l_row = f_row + f_drow * i;
        int l_col = f_col + f_dcol * i;
        if ((l_row < 0) || (l_row >= l_rows) || (l_col < 0) || (l_col >= l_cols))
        {
            return false;
        }

        if (f_mtx[l_row][l_col] != l_xmas[i])
        {
            return false;
        }
    }

    return true;
}

int Advent4::countMasX(const std::vector<std::vector<char>> &f_mtx) const
{
    int l_count = 0;

    for (int i = 1; i < (f_mtx.size() - 1); i++)
    {
        for (int j = 1; j < (f_mtx[i].size() - 1); j++)
        {
            if (isMasX(f_mtx, i, j))
            {
                l_count++;
            }
        }
    }

    return l_count;
}

bool Advent4::isMasX(const std::vector<std::vector<char>> &f_mtx, const int f_row, const int f_col) const
{
    const int l_dirs[2][2] = {
        {-1, -1},
        {-1, 1}};

    for (int i = 0; i < 2; i++)
    {
        if (!isMasAtDirs(f_mtx, f_row, f_col, l_dirs[i][0], l_dirs[i][1]))
        {
            return false;
        }
    }

    return true;
}

bool Advent4::isMasAtDirs(const std::vector<std::vector<char>> &f_mtx, const int f_row, const int f_col, const int f_drow, const int f_dcol) const
{
    const int l_signs[2] = {1, -1};
    const char *l_mas = "MAS";
    for (int i = 0; i < 2; i++)
    {
        int l_drow = l_signs[i] * f_drow;
        int l_dcol = l_signs[i] * f_dcol;
        int j;
        for (j = 0; j < 3; j++)
        {
            int l_row = f_row + l_drow - l_drow * j;
            int l_col = f_col + l_dcol - l_dcol * j;
            if (f_mtx[l_row][l_col] != l_mas[j])
            {
                break;
            }
        }
        if (j == 3)
        {
            return true;
        }
    }

    return false;
}
