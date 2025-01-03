#ifndef ADVENT_16_HPP
#define ADVENT_16_HPP

#include <string>
#include <vector>
#include <cstdint>

struct Program
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    std::vector<uint8_t> ops;
};

union Cpu
{
    struct Registers
    {
        uint64_t reg0;
        uint64_t reg1;
        uint64_t reg2;
        uint64_t reg3;
        uint64_t regA;
        uint64_t regB;
        uint64_t regC;
        uint64_t reg7;
    } regs;

    uint64_t combo[8];

    Cpu() : combo{0, 1, 2, 3, 0, 0, 0, 0} {}
};

class Advent17
{
public:
    std::string solvePartOne(const std::string &f_inputPath);
    uint64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readProgram(const std::string &f_filePath, Program &f_outProgram) const;
    std::string runProgram(Program &f_program) const;
    bool recursiveFindNextA(Program &f_program, const int f_idx, const uint64_t f_prevA, uint64_t &f_outA) const;
};

#endif