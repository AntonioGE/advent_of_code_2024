#ifndef ADVENT_7_HPP
#define ADVENT_7_HPP

#include <string>
#include <vector>
#include <cstdint>

struct Equation
{
    int64_t result;
    std::vector<int> operands;
};

enum class Operator : int
{
    Add = 0,
    Multiply,
    Concat
};

class Advent7
{
public:
    int64_t solvePartOne(const std::string &f_inputPath);
    int64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readEquations(const std::string &f_filePath, std::vector<Equation> &f_outEquations) const;
    int64_t sumValidEquations(const std::vector<Equation> &f_equations, const std::vector<Operator> &f_validOperators) const;
    bool isEquationValid(const Equation &f_equation, const std::vector<Operator> &f_validOperators) const;
    bool testPossibleOperators(const Equation &f_equation, std::vector<Operator> f_operators, const int f_pos, const std::vector<Operator> &f_validOperators) const;
    bool areOperatorsValid(const Equation &f_equation, const std::vector<Operator> f_operators) const;
    int64_t applyOperators(const std::vector<int> &f_operands, const std::vector<Operator> f_operators) const;
    int64_t applyOperator(const Operator f_operator, const int64_t f_lhs, const int64_t f_rhs) const;
};

#endif