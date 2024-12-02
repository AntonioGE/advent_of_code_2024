#ifndef ADVENT_2_HPP
#define ADVENT_2_HPP

#include <string>
#include <vector>

class Advent2
{
public:
    int solvePartOne(const std::string &f_inputPath);
    int solvePartTwo(const std::string &f_inputPath);

private:
    int readReportsFromFile(const std::string &f_filePath, std::vector<std::vector<int>> &f_outReports) const;
    int countSafeReports(const std::vector<std::vector<int>> &f_reports) const;
    bool isReportSafe(const std::vector<int> &f_report) const;
    bool haveSameSign(const int f_a, const int f_b) const;
    int countSafeReportsWithTol(const std::vector<std::vector<int>> &f_reports) const;
    bool isReportSafeWithTol(const std::vector<int> &f_report) const;

};

#endif