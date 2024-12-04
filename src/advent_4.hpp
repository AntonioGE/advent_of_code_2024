#ifndef ADVENT_4_HPP
#define ADVENT_4_HPP

#include <string>
#include <vector>

class Advent4
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readFileAsCharMtx(const std::string &f_filePath, std::vector<std::vector<char>> &f_outMtx) const;
    int countXmas(const std::vector<std::vector<char>> &f_mtx) const;
    bool isXmasAtDir(const std::vector<std::vector<char>> &f_mtx, const int f_row, const int f_col, const int f_drow, const int f_dcol) const;
    int countMasX(const std::vector<std::vector<char>> &f_mtx) const;
    bool isMasX(const std::vector<std::vector<char>> &f_mtx, const int f_row, const int f_col) const;
    bool isMasAtDirs(const std::vector<std::vector<char>> &f_mtx, const int f_row, const int f_col, const int f_drow, const int f_dcol) const;
};

#endif