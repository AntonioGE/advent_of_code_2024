#include "advent_5.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(5);

    Advent5 l_advent5;
    std::cout << "Result Part One: " << l_advent5.solvePartOne("res/input_5.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent5.solvePartTwo("res/input_5.txt") << std::endl;

    return 0;
}

int Advent5::solvePartOne(const std::string &f_inputPath)
{
    std::vector<Rule> l_rules;
    std::vector<Update> l_updates;
    if (readRulesAndUpdates(f_inputPath, l_rules, l_updates) != 0)
    {
        return -1;
    }

    return sumValidUpdatesMedian(l_rules, l_updates);
}

int Advent5::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<Rule> l_rules;
    std::vector<Update> l_updates;
    if (readRulesAndUpdates(f_inputPath, l_rules, l_updates) != 0)
    {
        return -1;
    }

    return sumInvalidUpdatesMedian(l_rules, l_updates);
}

int Advent5::readRulesAndUpdates(const std::string &f_filePath, std::vector<Rule> &f_outRules, std::vector<Update> &f_outUpdates) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    bool l_readRules = true;
    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.size() < 4)
        {
            l_readRules = false;
            continue;
        }

        if (l_readRules)
        {
            Rule l_rule;
            char l_delimiter;

            std::stringstream l_ss(l_line);
            l_ss >> l_rule.hi >> l_delimiter >> l_rule.lo;

            f_outRules.push_back(l_rule);
        }
        else
        {
            Update l_update;

            std::stringstream l_ss(l_line);
            std::string l_token;
            while (std::getline(l_ss, l_token, ','))
            {
                l_update.push_back(std::stoi(l_token));
            }

            f_outUpdates.push_back(l_update);
        }
    }

    l_file.close();

    return 0; // Success
}

int Advent5::sumValidUpdatesMedian(const std::vector<Rule> &f_rules, const std::vector<Update> &f_updates) const
{
    int l_sum = 0;

    std::unordered_set<Rule> l_ruleSet(f_rules.begin(), f_rules.end());
    for (const Update &l_udpate : f_updates)
    {
        if (isUpdateValid(l_ruleSet, l_udpate))
        {
            l_sum += l_udpate[l_udpate.size() / 2];
        }
    }

    return l_sum;
}

bool Advent5::isUpdateValid(const std::unordered_set<Rule> &f_ruleSet, const Update &f_update) const
{
    for (int i = 0; i < (f_update.size() - 1); i++)
    {
        Rule l_rule{f_update[i], f_update[i + 1]};
        if (f_ruleSet.find(l_rule) == f_ruleSet.end())
        {
            return false;
        }
    }

    return true;
}

int Advent5::sumInvalidUpdatesMedian(const std::vector<Rule> &f_rules, const std::vector<Update> &f_updates) const
{
    int l_sum = 0;

    std::unordered_set<Rule> l_ruleSet(f_rules.begin(), f_rules.end());
    for (const Update &l_udpate : f_updates)
    {
        if (!isUpdateValid(l_ruleSet, l_udpate))
        {
            Update l_sortedUpdate = l_udpate;
            sortUpdate(l_ruleSet, l_sortedUpdate);
            l_sum += l_sortedUpdate[l_sortedUpdate.size() / 2];
        }
    }

    return l_sum;
}

void Advent5::sortUpdate(const std::unordered_set<Rule> &f_ruleSet, Update &f_update) const
{
    auto l_lambdaCompare = [&](int f_hi, int f_lo)
    {
        return f_ruleSet.find(Rule{f_hi, f_lo}) != f_ruleSet.end();
    };

    std::sort(f_update.begin(), f_update.end(), l_lambdaCompare);
}
