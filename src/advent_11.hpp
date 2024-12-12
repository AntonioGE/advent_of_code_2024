#ifndef ADVENT_11_HPP
#define ADVENT_11_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <utility>
#include <unordered_map>

typedef std::unordered_map<uint64_t, uint64_t> StoneMap;

class Advent11
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readStones(const std::string &f_filePath, StoneMap &f_stoneMap) const;
    uint64_t countBlinkStones(const StoneMap &f_stoneMap, const int f_numBlinks) const;
    void addStoneToMap(StoneMap &f_stoneMap, const uint64_t f_stone, const uint64_t f_factor) const;
    int numDigits(const uint64_t f_num) const;
    std::pair<uint64_t, uint64_t> split(const uint64_t f_num) const;
    int powerOf10(const int f_exponent) const;
    
};

#endif