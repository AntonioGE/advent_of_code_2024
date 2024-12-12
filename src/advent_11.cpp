#include "advent_11.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(11);

    Advent11 l_advent11;
    std::cout << "Result Part One: " << l_advent11.solvePartOne("res/input_11.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent11.solvePartTwo("res/input_11.txt") << std::endl;

    return 0;
}

uint64_t Advent11::solvePartOne(const std::string &f_inputPath)
{
    StoneMap l_stoneMap;
    if (readStones(f_inputPath, l_stoneMap) != 0)
    {
        return -1;
    }

    return countBlinkStones(l_stoneMap, 25);
}

uint64_t Advent11::solvePartTwo(const std::string &f_inputPath)
{
    StoneMap l_stoneMap;
    if (readStones(f_inputPath, l_stoneMap) != 0)
    {
        return -1;
    }

    return countBlinkStones(l_stoneMap, 75);
}

int Advent11::readStones(const std::string &f_filePath, StoneMap &f_stoneMap) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_stoneMap.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        std::istringstream l_iss(l_line);
        uint64_t l_stone;
        while (l_iss >> l_stone)
        {
            addStoneToMap(f_stoneMap, l_stone, 1);
        }
    }

    l_file.close();

    return 0; // Success
}

uint64_t Advent11::countBlinkStones(const StoneMap &f_stoneMap, const int f_numBlinks) const
{
    std::unordered_map<uint64_t, uint64_t> l_stoneMap = f_stoneMap;
    for (int i = 0; i < f_numBlinks; i++)
    {
        std::unordered_map<uint64_t, uint64_t> l_nextStoneMap;
        for (const auto &l_entry : l_stoneMap)
        {
            uint64_t l_stone = l_entry.first;
            uint64_t l_factor = l_entry.second;
            if (l_stone == 0)
            {
                addStoneToMap(l_nextStoneMap, 1, l_factor);
            }
            else if ((numDigits(l_stone) % 2) == 0)
            {
                std::pair<uint64_t, uint64_t> l_split = split(l_stone);
                addStoneToMap(l_nextStoneMap, l_split.first, l_factor);
                addStoneToMap(l_nextStoneMap, l_split.second, l_factor);
            }
            else
            {
                addStoneToMap(l_nextStoneMap, l_stone * 2024, l_factor);
            }
        }

        l_stoneMap = l_nextStoneMap;
    }

    uint64_t l_count = 0;
    for (const auto &l_entry : l_stoneMap)
    {
        l_count += l_entry.second;
    }

    return l_count;
}

void Advent11::addStoneToMap(StoneMap &f_stoneMap, const uint64_t f_stone, const uint64_t f_factor) const
{
    if (f_stoneMap.find(f_stone) == f_stoneMap.end())
    {
        f_stoneMap[f_stone] = f_factor;
    }
    else
    {
        f_stoneMap[f_stone] += f_factor;
    }
}

int Advent11::numDigits(const uint64_t f_num) const
{
    int l_numDigits = 1;
    uint64_t l_num = f_num;
    while (l_num >= 10)
    {
        l_num /= 10;
        l_numDigits++;
    }

    return l_numDigits;
}

std::pair<uint64_t, uint64_t> Advent11::split(const uint64_t f_num) const
{
    int l_powerOf10 = powerOf10(numDigits(f_num) / 2);
    uint64_t l_left = f_num / l_powerOf10;
    uint64_t l_right = f_num % l_powerOf10;
    return std::pair<uint64_t, uint64_t>(l_left, l_right);
}

int Advent11::powerOf10(const int f_exponent) const
{
    int l_value = 1;
    for (int i = 0; i < f_exponent; i++)
    {
        l_value *= 10;
    }
    return l_value;
}
