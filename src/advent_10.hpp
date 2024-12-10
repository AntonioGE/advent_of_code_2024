#ifndef ADVENT_10_HPP
#define ADVENT_10_HPP

#include <string>
#include <vector>
#include <cstdint>

typedef std::vector<std::vector<int8_t>> Map;
typedef std::vector<std::vector<int8_t>> Map;

struct Vec
{
    int row;
    int col;

    inline friend Vec operator+(const Vec &f_lhs, const Vec &f_rhs)
    {
        return Vec{f_lhs.row + f_rhs.row, f_lhs.col + f_rhs.col};
    }
};

class Advent10
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readMap(const std::string &f_filePath, Map &f_outMap) const;
    int sumTrailScores(const Map &f_map) const;
    int getTrailScore(const Map &f_map, Map &f_checkedMap, const Vec &f_pos) const;
    void advanceTrail(const Map &f_map, Map &f_checkedMap, const Vec &f_pos, int &f_score) const;
    bool canMoveToPos(const Map &f_map, const Map &f_checkedMap, const Vec &f_currPos, const Vec &f_nextPos) const;
    bool isInsideMap(const Map &f_map, const Vec &f_pos) const;
    Map initCheckedMap(const Map f_map) const;
    void clearCheckedMap(Map &f_checkedMap) const;
    int sumTrailRatings(const Map &f_map) const;
    int getTrailRating(const Map &f_map, const Vec &f_pos) const;
    void advanceTrailRatting(const Map &f_map, const Vec &f_pos, int &f_rating) const;
    bool canMoveToPos(const Map &f_map, const Vec &f_currPos, const Vec &f_nextPos) const;

};

#endif