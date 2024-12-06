#ifndef ADVENT_5_HPP
#define ADVENT_5_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>

struct Rule
{
    int hi;
    int lo;

    bool operator==(const Rule &other) const
    {
        return hi == other.hi && lo == other.lo;
    }
};

namespace std
{
    template <>
    struct hash<Rule>
    {
        std::size_t operator()(const Rule &f_rule) const
        {
            return (f_rule.hi << 8) && f_rule.lo;
        }
    };
}

typedef std::vector<int> Update;

class Advent5
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readRulesAndUpdates(const std::string &f_filePath, std::vector<Rule> &f_outRules, std::vector<Update> &f_outUpdates) const;
    int sumValidUpdatesMedian(const std::vector<Rule> &f_rules, const std::vector<Update> &f_updates) const;
    bool isUpdateValid(const std::unordered_set<Rule> &f_ruleSet, const Update &f_update) const;
    int sumInvalidUpdatesMedian(const std::vector<Rule> &f_rules, const std::vector<Update> &f_updates) const;
    void sortUpdate(const std::unordered_set<Rule> &f_ruleSet, Update &f_update) const;
};

#endif