#include "advent_17.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(17);

    Advent17 l_advent17;
    std::cout << "Result Part One: " << l_advent17.solvePartOne("res/input_17.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent17.solvePartTwo("res/input_17.txt") << std::endl;

    return 0;
}

std::string Advent17::solvePartOne(const std::string &f_inputPath)
{
    Program l_cpu;
    if (readProgram(f_inputPath, l_cpu) != 0)
    {
        return "Error";
    }

    return runProgram(l_cpu);
}

uint64_t Advent17::solvePartTwo(const std::string &f_inputPath)
{
    Program l_program;
    if (readProgram(f_inputPath, l_program) != 0)
    {
        return -1;
    }

    uint64_t l_regA = 0;
    recursiveFindNextA(l_program, 0, 0, l_regA);
    return l_regA;
}

int Advent17::readProgram(const std::string &f_filePath, Program &f_outProgram) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        std::istringstream l_iss(l_line);
        if (l_line.find("Register A:") != std::string::npos)
        {
            l_iss.ignore(12);
            l_iss >> f_outProgram.a;
        }
        else if (l_line.find("Register B:") != std::string::npos)
        {
            l_iss.ignore(12);
            l_iss >> f_outProgram.b;
        }
        else if (l_line.find("Register C:") != std::string::npos)
        {
            l_iss.ignore(12);
            l_iss >> f_outProgram.c;
        }
        else if (l_line.find("Program:") != std::string::npos)
        {
            l_iss.ignore(9);
            std::string programData;
            std::getline(l_iss, programData);
            std::istringstream programStream(programData);
            uint8_t value;
            std::string token;
            while (std::getline(programStream, token, ','))
            {
                uint8_t value = static_cast<uint8_t>(std::stoi(token));
                f_outProgram.ops.push_back(value);
            }
        }
    }

    l_file.close();

    return 0; // Success
}

std::string Advent17::runProgram(Program &f_program) const
{
    std::string l_out = "";

    Cpu l_cpu;
    l_cpu.regs.regA = f_program.a;
    l_cpu.regs.regB = f_program.b;
    l_cpu.regs.regC = f_program.c;

    uint8_t l_pc = 0;
    while (l_pc < (f_program.ops.size() - 1))
    {
        uint8_t l_opcode = f_program.ops[l_pc];
        uint8_t l_operand = f_program.ops[l_pc + 1];

        switch (l_opcode)
        {
        case 0:
            l_cpu.regs.regA = l_cpu.regs.regA >> l_cpu.combo[l_operand];
            break;
        case 1:
            l_cpu.regs.regB ^= l_operand;
            break;
        case 2:
            l_cpu.regs.regB = l_cpu.combo[l_operand] % 8;
            break;
        case 3:
            if (l_cpu.regs.regA != 0)
            {
                l_pc = l_operand;
                continue;
            }
            break;
        case 4:
            l_cpu.regs.regB ^= l_cpu.regs.regC;
            break;
        case 5:
            if (!l_out.empty())
            {
                l_out += ",";
            }
            l_out += ((l_cpu.combo[l_operand] % 8) + '0');
            break;
        case 6:
            l_cpu.regs.regB = l_cpu.regs.regA >> l_cpu.combo[l_operand];
            break;
        case 7:
            l_cpu.regs.regC = l_cpu.regs.regA >> l_cpu.combo[l_operand];
            break;
        default:
            break;
        }

        l_pc += 2;
    }

    return l_out;
}

bool Advent17::recursiveFindNextA(Program &f_program, const int f_idx, const uint64_t f_prevA, uint64_t &f_outA) const
{
    if (f_idx >= f_program.ops.size())
    {
        return true;
    }

    uint8_t l_targetOpcode = f_program.ops[f_program.ops.size() - 1 - f_idx];
    for (int i = 0; i < (1 << 3); i++)
    {
        uint64_t l_initRegA = (f_prevA << 3) | i;

        Cpu l_cpu;
        l_cpu.regs.regA = l_initRegA;
        l_cpu.regs.regB = f_program.b;
        l_cpu.regs.regC = f_program.c;

        uint8_t l_pc = 0;
        bool l_continue = true;
        while ((l_continue) && (l_pc < (f_program.ops.size() - 1)))
        {
            uint8_t l_opcode = f_program.ops[l_pc];
            uint8_t l_operand = f_program.ops[l_pc + 1];

            switch (l_opcode)
            {
            case 0:
                l_cpu.regs.regA = l_cpu.regs.regA >> l_cpu.combo[l_operand];
                break;
            case 1:
                l_cpu.regs.regB ^= l_operand;
                break;
            case 2:
                l_cpu.regs.regB = l_cpu.combo[l_operand] % 8;
                break;
            case 3:
                if (l_cpu.regs.regA != 0)
                {
                    l_pc = l_operand;
                    continue;
                }
                break;
            case 4:
                l_cpu.regs.regB ^= l_cpu.regs.regC;
                break;
            case 5:
                if ((l_cpu.combo[l_operand] % 8) == l_targetOpcode)
                {
                    if (recursiveFindNextA(f_program, f_idx + 1, l_initRegA, f_outA))
                    {
                        if (f_outA == 0)
                        {
                            f_outA = l_cpu.regs.regA;
                        }
                        return true;
                    }
                }
                l_continue = false;
                break;
            case 6:
                l_cpu.regs.regB = l_cpu.regs.regA >> l_cpu.combo[l_operand];
                break;
            case 7:
                l_cpu.regs.regC = l_cpu.regs.regA >> l_cpu.combo[l_operand];
                break;
            default:
                break;
            }

            l_pc += 2;
        }
    };

    return false;
}