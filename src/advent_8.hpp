#ifndef ADVENT_8_HPP
#define ADVENT_8_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>

typedef std::vector<std::vector<char>> Map;

struct Vec
{
    int row;
    int col;

    bool operator==(const Vec &f_other) const
    {
        return (row == f_other.row) && (col == f_other.col);
    }

    inline friend Vec operator+(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row + f_rhs.row, f_lhs.col + f_rhs.col};
    }

    inline friend Vec operator-(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row - f_rhs.row, f_lhs.col - f_rhs.col};
    }
};

namespace std
{
    template <>
    struct hash<Vec>
    {
        std::size_t operator()(const Vec &f_vec) const
        {
            std::size_t l_h1 = std::hash<int>()(f_vec.row);
            std::size_t l_h2 = std::hash<int>()(f_vec.col);
            return l_h1 ^ (l_h2 << 1);
        }
    };
}

typedef std::unordered_map<char, std::vector<Vec>> AntenaMap;

typedef std::unordered_set<Vec> AntinodeSet;

class Advent8
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readMap(const std::string &f_filePath, Map &f_outMap) const;
    int countAntinodes(const Map &f_map) const;
    AntenaMap findAntenas(const Map &f_map) const;
    AntinodeSet getAntinodeSet(const AntenaMap &f_antenaMap) const;
    std::pair<Vec, Vec> getAntinodePair(const Vec &f_antena1, const Vec &f_antena2) const;
    bool isInsideMap(const Map &f_map, const Vec &f_pos) const;
    int countResonantAntinodes(const Map &f_map) const;
    AntinodeSet getResonantAntinodeSet(const Map &f_map, const AntenaMap &f_antenaMap) const;
    std::vector<Vec> getResonantAntinodes(const Map &f_map, const Vec &f_antena1, const Vec &f_antena2) const;
};

#endif