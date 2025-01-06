#include "advent_19.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(19);

    Advent19 l_advent19;
    std::cout << "Result Part One: " << l_advent19.solvePartOne("res/input_19.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent19.solvePartTwo("res/input_19.txt") << std::endl;

    return 0;
}

uint64_t Advent19::solvePartOne(const std::string &f_inputPath)
{
    std::vector<std::string> l_towels;
    std::vector<std::string> l_designs;
    if (readTowelsAndDesigns(f_inputPath, l_towels, l_designs) != 0)
    {
        return -1;
    }

    return countValidDesigns(l_towels, l_designs);
}

uint64_t Advent19::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<std::string> l_towels;
    std::vector<std::string> l_designs;
    if (readTowelsAndDesigns(f_inputPath, l_towels, l_designs) != 0)
    {
        return -1;
    }

    return countDesignsCombinations(l_towels, l_designs);
}

int Advent19::readTowelsAndDesigns(const std::string &f_filePath, std::vector<std::string> &f_outTowels, std::vector<std::string> &f_outDesigns) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outTowels.clear();
    f_outDesigns.clear();

    bool l_readTowels = true;
    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.empty())
        {
            l_readTowels = false;
            continue;
        }

        if (l_readTowels)
        {
            std::stringstream l_ss(l_line);
            std::string l_towel;
            while (std::getline(l_ss, l_towel, ','))
            {
                l_towel.erase(remove_if(l_towel.begin(), l_towel.end(), isspace), l_towel.end());
                f_outTowels.push_back(l_towel);
            }
        }
        else
        {
            f_outDesigns.push_back(l_line);
        }
    }

    l_file.close();

    return 0;
}

uint64_t Advent19::countValidDesigns(const std::vector<std::string> &f_towels, const std::vector<std::string> &f_designs) const
{
    uint64_t l_count = 0;
    for (const std::string &l_design : f_designs)
    {
        if (isDesignValid(f_towels, l_design))
        {
            l_count++;
        }
    }
    return l_count;
}

bool Advent19::isDesignValid(const std::vector<std::string> &f_towels, const std::string &f_design) const
{
    std::unordered_set<int> l_memo;
    return isDesignValidRecursive(f_towels, f_design, 0, l_memo);
}

bool Advent19::isDesignValidRecursive(const std::vector<std::string> &f_towels, const std::string &f_design, const int f_letterIdx, std::unordered_set<int> &f_memo) const
{
    if (f_letterIdx == f_design.size())
    {
        return true;
    }

    if (f_memo.count(f_letterIdx))
    {
        return false;
    }

    for (const std::string &l_towel : f_towels)
    {
        if (f_design.compare(f_letterIdx, l_towel.size(), l_towel) == 0)
        {
            if (isDesignValidRecursive(f_towels, f_design, f_letterIdx + l_towel.size(), f_memo))
            {
                return true;
            }
        }
    }

    f_memo.insert(f_letterIdx);
    return false;
}

uint64_t Advent19::countDesignsCombinations(const std::vector<std::string> &f_towels, const std::vector<std::string> &f_designs) const
{
    uint64_t l_count = 0;
    for (const std::string &l_design : f_designs)
    {
        l_count += countDesignCombinations(f_towels, l_design);
    }
    return l_count;
}

uint64_t Advent19::countDesignCombinations(const std::vector<std::string> &f_towels, const std::string &f_design) const
{
    std::unordered_map<int, uint64_t> l_memo;
    return countDesignCombinationsRecursive(f_towels, f_design, 0, l_memo);
}

uint64_t Advent19::countDesignCombinationsRecursive(const std::vector<std::string> &f_towels, const std::string &f_design, const int f_letterIdx, std::unordered_map<int, uint64_t> &f_memo) const
{
    if (f_letterIdx == f_design.size())
    {
        return 1;
    }

    if (f_memo.count(f_letterIdx))
    {
        return f_memo[f_letterIdx];
    }

    uint64_t l_count = 0;
    for (const std::string &l_towel : f_towels)
    {
        if (f_design.compare(f_letterIdx, l_towel.size(), l_towel) == 0)
        {
            l_count += countDesignCombinationsRecursive(f_towels, f_design, f_letterIdx + l_towel.size(), f_memo);
        }
    }

    f_memo[f_letterIdx] = l_count;
    return l_count;
}
