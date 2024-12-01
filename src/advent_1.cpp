#include "advent_1.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(1);

    Advent1 l_advent1;
    std::cout << "Result Part One: " << l_advent1.solvePartOne("res/input_1.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent1.solvePartTwo("res/input_1.txt") << std::endl;

    return 0;
}

int Advent1::solvePartOne(const std::string &f_inputPath)
{
    std::vector<int> l_leftList;
    std::vector<int> l_rightList;
    if (readTwoListsFromFile(f_inputPath, l_leftList, l_rightList))
    {
        return -1;
    }

    return getTotalDistance(l_leftList, l_rightList);
}

int Advent1::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<int> l_leftList;
    std::vector<int> l_rightList;
    if (readTwoListsFromFile(f_inputPath, l_leftList, l_rightList))
    {
        return -1;
    }

    return getSimilarity(l_leftList, l_rightList);
}

int Advent1::readTwoListsFromFile(const std::string &f_filePath, std::vector<int> &f_outLeftList, std::vector<int> &f_outRightList) const
{
    std::ifstream l_file(f_filePath);

    if (!l_file)
    {
        std::cerr << "Error: Could not open file '" << f_filePath << "'" << std::endl;
        return -1; // Error
    }

    int l_num1, l_num2;
    while (l_file >> l_num1 >> l_num2)
    {
        f_outLeftList.push_back(l_num1);
        f_outRightList.push_back(l_num2);
    }

    l_file.close();

    return 0; // Success
}

int Advent1::getTotalDistance(const std::vector<int> &f_leftList, const std::vector<int> &f_rightList) const
{
    std::vector<int> l_leftListSorted = sortedCopy(f_leftList);
    std::vector<int> l_rightListSorted = sortedCopy(f_rightList);

    int l_totalDistance = 0;
    size_t l_size = std::min(l_leftListSorted.size(), l_rightListSorted.size());
    for (size_t i = 0; i < l_size; i++)
    {
        l_totalDistance += std::abs(l_leftListSorted[i] - l_rightListSorted[i]);
    }

    return l_totalDistance;
}

std::vector<int> Advent1::sortedCopy(const std::vector<int> &f_list) const
{
    std::vector<int> l_sortedList = f_list;
    std::sort(l_sortedList.begin(), l_sortedList.end());
    return l_sortedList;
}

int Advent1::getSimilarity(const std::vector<int> &f_leftList, const std::vector<int> &f_rightList) const
{
    int l_similarity = 0;
    for(const int l_leftNumber : f_leftList)
    {
        l_similarity += l_leftNumber * getOccurrencesCount(l_leftNumber, f_rightList);
    }

    return l_similarity;
}

int Advent1::getOccurrencesCount(const int f_leftNumber, const std::vector<int> &f_rightList) const
{
    int l_occurrencesCount = 0;
    for (const int l_rightNumber : f_rightList)
    {
        if (f_leftNumber == l_rightNumber)
        {
            l_occurrencesCount++;
        }
    }
    return l_occurrencesCount;
}
