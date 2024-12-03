#ifndef ADVENT_3_HPP
#define ADVENT_3_HPP

#include <string>
#include <vector>

class Advent3
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readFileAsString(const std::string &f_filePath, std::string &f_outString) const;
    int sumValidMults(const std::string &f_memory) const;
    bool isValidMult(const char *f_begin, const char *f_end, int &f_outA, int &f_outB) const;
    int getNumberLength(const char *f_begin, const char *f_end) const;
    bool isCharDigit(const char f_digit) const;
    int parseInt(const char *f_begin, const int f_size) const;
    int sumValidAndEnabledMults(const std::string &f_memory) const;
};

#endif