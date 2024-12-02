#include "advent_2.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(2);

    Advent2 l_advent2;
    std::cout << "Result Part One: " << l_advent2.solvePartOne("res/input_2.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent2.solvePartTwo("res/input_2.txt") << std::endl;

    return 0;
}

int Advent2::solvePartOne(const std::string &f_inputPath)
{
    std::vector<std::vector<int>> l_reports;
    if (readReportsFromFile(f_inputPath, l_reports) != 0)
    {
        return -1; // Error
    }

    return countSafeReports(l_reports);
}

int Advent2::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<std::vector<int>> l_reports;
    if (readReportsFromFile(f_inputPath, l_reports) != 0)
    {
        return -1; // Error
    }

    return countSafeReportsWithTol(l_reports);
}

int Advent2::readReportsFromFile(const std::string &f_filePath, std::vector<std::vector<int>> &f_outReports) const
{
    std::ifstream l_file(f_filePath);

    if (!l_file)
    {
        std::cerr << "Error: Could not open file '" << f_filePath << "'" << std::endl;
        return -1; // Error
    }

    f_outReports.clear();

    std::string l_line;
    std::stringstream l_stringStream;
    while (std::getline(l_file, l_line))
    {
        l_stringStream.str(l_line);
        l_stringStream.clear();

        std::vector<int> l_report;

        int l_num;
        while (l_stringStream >> l_num)
        {
            l_report.push_back(l_num);
        }

        f_outReports.push_back(l_report);
    }

    l_file.close();

    return 0; // Success
}

int Advent2::countSafeReports(const std::vector<std::vector<int>> &f_reports) const
{
    int l_count = 0;

    for (const std::vector<int> &l_report : f_reports)
    {
        if (isReportSafe(l_report))
        {
            l_count++;
        }
    }

    return l_count;
}

bool Advent2::isReportSafe(const std::vector<int> &f_report) const
{
    int l_lastDiff;
    for (size_t i = 1; i < f_report.size(); i++)
    {
        int l_diff = f_report[i] - f_report[i - 1];
        int l_absDiff = std::abs(l_diff);
        if ((l_absDiff < 1) || (l_absDiff > 3) || ((i > 1) && !haveSameSign(l_diff, l_lastDiff)))
        {
            return false;
        }
        l_lastDiff = l_diff;
    }

    return true;
}

bool Advent2::haveSameSign(const int f_a, const int f_b) const
{
    return (f_a ^ f_b) >= 0;
}

int Advent2::countSafeReportsWithTol(const std::vector<std::vector<int>> &f_reports) const
{
    int l_count = 0;

    for (const std::vector<int> &l_report : f_reports)
    {
        if (isReportSafeWithTol(l_report))
        {
            l_count++;
        }
    }

    return l_count;
}

bool Advent2::isReportSafeWithTol(const std::vector<int> &f_report) const
{
    for (size_t i = 0; i < f_report.size(); i++)
    {
        std::vector<int> l_reducedReport = f_report;
        l_reducedReport.erase(l_reducedReport.begin() + i);

        if(isReportSafe(l_reducedReport))
        {
            return true;
        }
    }

    return false;
}
