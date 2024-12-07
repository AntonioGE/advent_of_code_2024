#include "advent_7.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(7);

    Advent7 l_advent7;
    std::cout << "Result Part One: " << l_advent7.solvePartOne("res/input_7.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent7.solvePartTwo("res/input_7.txt") << std::endl;

    return 0;
}

int64_t Advent7::solvePartOne(const std::string &f_inputPath)
{
    std::vector<Equation> l_equations;
    if (readEquations(f_inputPath, l_equations) != 0)
    {
        return -1;
    }

    return sumValidEquations(l_equations, {Operator::Add, Operator::Multiply});
}

int64_t Advent7::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<Equation> l_equations;
    if (readEquations(f_inputPath, l_equations) != 0)
    {
        return -1;
    }

    return sumValidEquations(l_equations, {Operator::Add, Operator::Multiply, Operator::Concat});
}

int Advent7::readEquations(const std::string &f_filePath, std::vector<Equation> &f_outEquations) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outEquations.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        size_t l_colonPos = l_line.find(':');
        if (l_colonPos == std::string::npos)
        {
            continue;
        }

        Equation l_equation;
        l_equation.result = std::stoll(l_line.substr(0, l_colonPos));

        std::istringstream l_ss(l_line.substr(l_colonPos + 1));
        int l_operand;
        while (l_ss >> l_operand)
        {
            l_equation.operands.push_back(l_operand);
        }

        f_outEquations.push_back(l_equation);
    }

    l_file.close();

    return 0; // Success
}

int64_t Advent7::sumValidEquations(const std::vector<Equation> &f_equations, const std::vector<Operator> &f_validOperators) const
{
    int64_t l_sum = 0;

    for (const Equation &l_equation : f_equations)
    {
        if (isEquationValid(l_equation, f_validOperators))
        {
            l_sum += l_equation.result;
        }
    }

    return l_sum;
}

bool Advent7::isEquationValid(const Equation &f_equation, const std::vector<Operator> &f_validOperators) const
{
    std::vector<Operator> l_operators(f_equation.operands.size() - 1);
    return testPossibleOperators(f_equation, l_operators, 0, f_validOperators);
}

bool Advent7::testPossibleOperators(const Equation &f_equation, std::vector<Operator> f_operators, const int f_pos, const std::vector<Operator> &f_validOperators) const
{
    if (f_pos == f_operators.size())
    {
        return areOperatorsValid(f_equation, f_operators);
    }

    for (const Operator &l_operator : f_validOperators)
    {
        f_operators[f_pos] = l_operator;
        if (testPossibleOperators(f_equation, f_operators, f_pos + 1, f_validOperators))
        {
            return true;
        }
    }

    return false;
}

bool Advent7::areOperatorsValid(const Equation &f_equation, const std::vector<Operator> f_operators) const
{
    return f_equation.result == applyOperators(f_equation.operands, f_operators);
}

int64_t Advent7::applyOperators(const std::vector<int> &f_operands, const std::vector<Operator> f_operators) const
{
    int64_t l_result = f_operands[0];
    for (int i = 0; i < f_operators.size(); i++)
    {
        l_result = applyOperator(f_operators[i], l_result, f_operands[i + 1]);
    }
    return l_result;
}

int64_t Advent7::applyOperator(const Operator f_operator, const int64_t f_lhs, const int64_t f_rhs) const
{
    switch (f_operator)
    {
    case Operator::Add:
        return f_lhs + f_rhs;
    case Operator::Multiply:
        return f_lhs * f_rhs;
    case Operator::Concat:
        return std::stoll(std::to_string(f_lhs) + std::to_string(f_rhs));
    default:
        return 0;
    }
}
