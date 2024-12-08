#include "advent_8.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(8);

    Advent8 l_advent8;
    std::cout << "Result Part One: " << l_advent8.solvePartOne("res/input_8.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent8.solvePartTwo("res/input_8.txt") << std::endl;

    return 0;
}

int Advent8::solvePartOne(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return countAntinodes(l_map);
}

int Advent8::solvePartTwo(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return countResonantAntinodes(l_map);
}

int Advent8::readMap(const std::string &f_filePath, Map &f_outMap) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outMap.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.empty())
        {
            continue;
        }

        std::vector<char> l_charLine(l_line.begin(), l_line.end());
        f_outMap.push_back(l_charLine);
    }

    l_file.close();

    return 0; // Success
}

int Advent8::countAntinodes(const Map &f_map) const
{
    int l_count = 0;

    AntenaMap l_antenaMap = findAntenas(f_map);
    AntinodeSet l_antinodeSet = getAntinodeSet(l_antenaMap);
    for (const Vec &l_antinode : l_antinodeSet)
    {
        if (isInsideMap(f_map, l_antinode))
        {
            l_count++;
        }
    }

    return l_count;
}

AntenaMap Advent8::findAntenas(const Map &f_map) const
{
    AntenaMap l_antenaMap;
    for (int i = 0; i < f_map.size(); i++)
    {
        for (int j = 0; j < f_map[i].size(); j++)
        {
            const char l_cell = f_map[i][j];
            if (l_cell != '.')
            {
                l_antenaMap[l_cell].push_back(Vec{i, j});
            }
        }
    }
    return l_antenaMap;
}

AntinodeSet Advent8::getAntinodeSet(const AntenaMap &f_antenaMap) const
{
    AntinodeSet l_antinodeSet;

    for (const auto &l_entry : f_antenaMap)
    {
        const std::vector<Vec> &l_antenas = l_entry.second;
        for (int i = 0; i < l_antenas.size(); i++)
        {
            for (int j = i + 1; j < l_antenas.size(); j++)
            {
                std::pair<Vec, Vec> l_antinodePair = getAntinodePair(l_antenas[i], l_antenas[j]);
                l_antinodeSet.insert(l_antinodePair.first);
                l_antinodeSet.insert(l_antinodePair.second);
            }
        }
    }

    return l_antinodeSet;
}

std::pair<Vec, Vec> Advent8::getAntinodePair(const Vec &f_antena1, const Vec &f_antena2) const
{
    std::pair<Vec, Vec> l_antinodePair;

    Vec l_diff = f_antena1 - f_antena2;
    l_antinodePair.first = f_antena1 + l_diff;
    l_antinodePair.second = f_antena2 - l_diff;

    return l_antinodePair;
}

bool Advent8::isInsideMap(const Map &f_map, const Vec &f_pos) const
{
    return (f_pos.row >= 0) && (f_pos.row < f_map.size()) && (f_pos.col >= 0) && (f_pos.col < f_map[0].size());
}

int Advent8::countResonantAntinodes(const Map &f_map) const
{
    int l_count = 0;

    AntenaMap l_antenaMap = findAntenas(f_map);
    AntinodeSet l_resonantAntinodeSet = getResonantAntinodeSet(f_map, l_antenaMap);
    for (const Vec &l_antinode : l_resonantAntinodeSet)
    {
        l_count++;
    }

    return l_count;
}

AntinodeSet Advent8::getResonantAntinodeSet(const Map &f_map, const AntenaMap &f_antenaMap) const
{
    AntinodeSet l_antinodeSet;

    for (const auto &l_entry : f_antenaMap)
    {
        const std::vector<Vec> &l_antenas = l_entry.second;
        for (int i = 0; i < l_antenas.size(); i++)
        {
            for (int j = i + 1; j < l_antenas.size(); j++)
            {
                std::vector<Vec> l_antinodes = getResonantAntinodes(f_map, l_antenas[i], l_antenas[j]);
                l_antinodeSet.insert(l_antinodes.begin(), l_antinodes.end());
            }
        }
    }

    return l_antinodeSet;
}

std::vector<Vec> Advent8::getResonantAntinodes(const Map &f_map, const Vec &f_antena1, const Vec &f_antena2) const
{
    std::vector<Vec> l_antinodes;

    Vec l_diff = f_antena1 - f_antena2;
    for (Vec l_antinode = f_antena2; isInsideMap(f_map, l_antinode); l_antinode = l_antinode + l_diff)
    {
        l_antinodes.push_back(l_antinode);
    }
    for (Vec l_antinode = f_antena2 - l_diff; isInsideMap(f_map, l_antinode); l_antinode = l_antinode - l_diff)
    {
        l_antinodes.push_back(l_antinode);
    }

    return l_antinodes;
}
