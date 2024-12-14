#include "advent_13.hpp"

#include <iostream>
#include <fstream>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(13);

    Advent13 l_advent13;
    std::cout << "Result Part One: " << l_advent13.solvePartOne("res/input_13.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent13.solvePartTwo("res/input_13.txt") << std::endl;

    return 0;
}

uint64_t Advent13::solvePartOne(const std::string &f_inputPath)
{
    std::vector<Machine> l_machines;
    if (readMachines(f_inputPath, l_machines) != 0)
    {
        return -1;
    }

    return sumTokens(l_machines);
}

uint64_t Advent13::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<Machine> l_machines;
    if (readMachines(f_inputPath, l_machines) != 0)
    {
        return -1;
    }

    return sumTokensHigh(l_machines);
}

int Advent13::readMachines(const std::string &f_filePath, std::vector<Machine> &f_outMachines) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outMachines.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_line.find("Button A") != std::string::npos)
        {
            Machine l_machine;

            sscanf(l_line.c_str(), "Button A: X+%lld, Y+%lld", &l_machine.A[0][0], &l_machine.A[1][0]);

            std::getline(l_file, l_line);
            sscanf(l_line.c_str(), "Button B: X+%lld, Y+%lld", &l_machine.A[0][1], &l_machine.A[1][1]);

            std::getline(l_file, l_line);
            sscanf(l_line.c_str(), "Prize: X=%lld, Y=%lld", &l_machine.b[0], &l_machine.b[1]);

            f_outMachines.push_back(l_machine);
        }
    }

    l_file.close();

    return 0; // Success
}

uint64_t Advent13::sumTokens(const std::vector<Machine> &f_machines) const
{
    uint64_t l_sum = 0;

    for (const Machine &l_machine : f_machines)
    {
        Solution l_solution;
        if (trySolve(l_machine, l_solution) && isSolutionValid(l_solution))
        {
            l_sum += l_solution.x[0] * 3 + l_solution.x[1];
        }
    }

    return l_sum;
}

bool Advent13::trySolve(const Machine &f_machine, Solution &f_outSolution) const
{
    int64_t l_det = determinant(f_machine.A);

    if (l_det == 0)
    {
        return false;
    }

    int64_t l_mtxA[2][2];
    l_mtxA[0][0] = f_machine.b[0];
    l_mtxA[1][0] = f_machine.b[1];
    l_mtxA[0][1] = f_machine.A[0][1];
    l_mtxA[1][1] = f_machine.A[1][1];
    int64_t l_detA = determinant(l_mtxA);
    if ((l_detA % l_det) != 0)
    {
        return false;
    }
    f_outSolution.x[0] = l_detA / l_det;

    int64_t l_mtxB[2][2];
    l_mtxB[0][0] = f_machine.A[0][0];
    l_mtxB[1][0] = f_machine.A[1][0];
    l_mtxB[0][1] = f_machine.b[0];
    l_mtxB[1][1] = f_machine.b[1];
    int64_t l_detB = determinant(l_mtxB);
    if ((l_detB % l_det) != 0)
    {
        return false;
    }
    f_outSolution.x[1] = l_detB / l_det;

    return true;
}

int64_t Advent13::determinant(const int64_t f_mtx[2][2]) const
{
    return f_mtx[0][0] * f_mtx[1][1] - f_mtx[0][1] * f_mtx[1][0];
}

bool Advent13::isSolutionValid(const Solution &f_solution) const
{
    return (f_solution.x[0] <= 100) && (f_solution.x[1] <= 100);
}

bool Advent13::isNumPressesValid(const int64_t f_numPresses) const
{
    return f_numPresses <= 100;
}

uint64_t Advent13::sumTokensHigh(const std::vector<Machine> &f_machines) const
{
    uint64_t l_sum = 0;

    std::vector<Machine> l_highMachines = f_machines;
    for (Machine &l_machine : l_highMachines)
    {
        l_machine.b[0] += 10000000000000;
        l_machine.b[1] += 10000000000000;
    }

    for (const Machine &l_machine : l_highMachines)
    {
        Solution l_solution;
        if (trySolve(l_machine, l_solution))
        {
            l_sum += l_solution.x[0] * 3 + l_solution.x[1];
        }
    }

    return l_sum;
}
