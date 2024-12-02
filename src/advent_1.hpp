#ifndef ADVENT_1_HPP
#define ADVENT_1_HPP

#include <string>
#include <vector>

class Advent1
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readTwoListsFromFile(const std::string &f_filePath, std::vector<int> &f_list1, std::vector<int> &f_list2) const;
    int getTotalDistance(const std::vector<int> &f_leftList, const std::vector<int> &f_rightList) const;
    std::vector<int> sortedCopy(const std::vector<int> &f_list) const;
    int getSimilarity(const std::vector<int> &f_leftList, const std::vector<int> &f_rightList) const;
    int getOccurrencesCount(const int f_leftNumber, const std::vector<int> &f_rightList) const;
};

#endif