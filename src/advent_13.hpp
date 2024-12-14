#ifndef ADVENT_13_HPP
#define ADVENT_13_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <utility>

struct Machine
{
    int64_t A[2][2];
    int64_t b[2];
};

struct Solution
{
    int64_t x[2];
};

class Advent13
{
public:
    uint64_t solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readMachines(const std::string &f_filePath, std::vector<Machine> &f_outMachines) const;
    uint64_t sumTokens(const std::vector<Machine> &f_machines) const;
    bool trySolve(const Machine &f_machine, Solution &f_outSolution) const;
    int64_t determinant(const int64_t f_mtx[2][2]) const;
    bool isSolutionValid(const Solution &f_solution) const;
    bool isNumPressesValid(const int64_t f_numPresses) const;
    uint64_t sumTokensHigh(const std::vector<Machine> &f_machines) const;
};

#endif