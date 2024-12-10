#include "advent_10.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "advent_common.hpp"

const Vec g_dirTable[4] = {
    Vec{0, -1},
    Vec{0, 1},
    Vec{-1, 0},
    Vec{1, 0}};

int main()
{
    AdventCommon::printDay(10);

    Advent10 l_advent10;
    std::cout << "Result Part One: " << l_advent10.solvePartOne("res/input_10.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent10.solvePartTwo("res/input_10.txt") << std::endl;

    return 0;
}

int Advent10::solvePartOne(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return sumTrailScores(l_map);
}

int Advent10::solvePartTwo(const std::string &f_inputPath)
{
    Map l_map;
    if (readMap(f_inputPath, l_map) != 0)
    {
        return -1;
    }

    return sumTrailRatings(l_map);
}

int Advent10::readMap(const std::string &f_filePath, Map &f_outMap) const
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

        std::vector<int8_t> l_intLine(l_line.size());
        for (int i = 0; i < l_line.size(); i++)
        {
            l_intLine[i] = l_line[i] - '0';
        }
        f_outMap.push_back(l_intLine);
    }

    l_file.close();

    return 0; // Success
}

int Advent10::sumTrailScores(const Map &f_map) const
{
    int l_sum = 0;

    Map l_checkedMap = initCheckedMap(f_map);
    for (int i = 0; i < f_map.size(); i++)
    {
        for (int j = 0; j < f_map[i].size(); j++)
        {
            if (f_map[i][j] == 0)
            {
                l_sum += getTrailScore(f_map, l_checkedMap, Vec{i, j});
            }
        }
    }
    return l_sum;
}

int Advent10::getTrailScore(const Map &f_map, Map &f_checkedMap, const Vec &f_start) const
{
    clearCheckedMap(f_checkedMap);
    int l_score = 0;
    advanceTrail(f_map, f_checkedMap, f_start, l_score);
    return l_score;
}

void Advent10::advanceTrail(const Map &f_map, Map &f_checkedMap, const Vec &f_pos, int &f_score) const
{
    if (f_map[f_pos.row][f_pos.col] == 9)
    {
        f_score++;
        f_checkedMap[f_pos.row][f_pos.col] = 1;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        Vec l_nextPos = f_pos + g_dirTable[i];
        if (canMoveToPos(f_map, f_checkedMap, f_pos, l_nextPos))
        {
            advanceTrail(f_map, f_checkedMap, l_nextPos, f_score);
            f_checkedMap[l_nextPos.row][l_nextPos.col] = 1;
        }
    }
}

bool Advent10::canMoveToPos(const Map &f_map, const Map &f_checkedMap, const Vec &f_currPos, const Vec &f_nextPos) const
{
    if (!isInsideMap(f_map, f_nextPos))
    {
        return false;
    }

    if (f_checkedMap[f_nextPos.row][f_nextPos.col])
    {
        return false;
    }

    int8_t l_currHeight = f_map[f_currPos.row][f_currPos.col];
    int8_t l_nextHeight = f_map[f_nextPos.row][f_nextPos.col];
    return l_nextHeight - l_currHeight == 1;
}

bool Advent10::isInsideMap(const Map &f_map, const Vec &f_pos) const
{
    return (f_pos.row >= 0) && (f_pos.row < f_map.size()) && (f_pos.col >= 0) && (f_pos.col < f_map[0].size());
}

Map Advent10::initCheckedMap(const Map f_map) const
{
    Map l_checkedMap(f_map.size());

    for (int i = 0; i < f_map.size(); i++)
    {
        l_checkedMap[i].resize(f_map[i].size(), 0);
    }

    return l_checkedMap;
}

void Advent10::clearCheckedMap(Map &f_checkedMap) const
{
    for (int i = 0; i < f_checkedMap.size(); i++)
    {
        for (int j = 0; j < f_checkedMap[j].size(); j++)
        {
            f_checkedMap[i][j] = 0;
        }
    }
}

int Advent10::sumTrailRatings(const Map &f_map) const
{
    int l_sum = 0;

    for (int i = 0; i < f_map.size(); i++)
    {
        for (int j = 0; j < f_map[i].size(); j++)
        {
            if (f_map[i][j] == 0)
            {
                l_sum += getTrailRating(f_map, Vec{i, j});
            }
        }
    }
    return l_sum;
}

int Advent10::getTrailRating(const Map &f_map, const Vec &f_pos) const
{
    int l_rating = 0;
    advanceTrailRatting(f_map, f_pos, l_rating);
    return l_rating;
}

void Advent10::advanceTrailRatting(const Map &f_map, const Vec &f_pos, int &f_rating) const
{
    if (f_map[f_pos.row][f_pos.col] == 9)
    {
        f_rating++;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        Vec l_nextPos = f_pos + g_dirTable[i];
        if (canMoveToPos(f_map, f_pos, l_nextPos))
        {
            advanceTrailRatting(f_map, l_nextPos, f_rating);
        }
    }
}

bool Advent10::canMoveToPos(const Map &f_map, const Vec &f_currPos, const Vec &f_nextPos) const
{
    if (!isInsideMap(f_map, f_nextPos))
    {
        return false;
    }

    int8_t l_currHeight = f_map[f_currPos.row][f_currPos.col];
    int8_t l_nextHeight = f_map[f_nextPos.row][f_nextPos.col];
    return l_nextHeight - l_currHeight == 1;
}
