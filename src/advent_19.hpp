#ifndef ADVENT_19_HPP
#define ADVENT_19_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>

class Advent19
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readTowelsAndDesigns(const std::string &f_filePath, std::vector<std::string> &f_outTowels, std::vector<std::string> &f_outDesigns) const;
    uint64_t countValidDesigns(const std::vector<std::string> &f_towels, const std::vector<std::string> &f_designs) const;
    bool isDesignValid(const std::vector<std::string> &f_towels, const std::string &f_design) const;
    bool isDesignValidRecursive(const std::vector<std::string> &f_towels, const std::string &f_design, const int f_letterIdx, std::unordered_set<int> &f_memo) const;
    uint64_t countDesignsCombinations(const std::vector<std::string> &f_towels, const std::vector<std::string> &f_designs) const;
    uint64_t countDesignCombinations(const std::vector<std::string> &f_towels, const std::string &f_design) const;
    uint64_t countDesignCombinationsRecursive(const std::vector<std::string> &f_towels, const std::string &f_design, const int f_letterIdx, std::unordered_map<int, uint64_t> &f_memo) const;
};

#endif