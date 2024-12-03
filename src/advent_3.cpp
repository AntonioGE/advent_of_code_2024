#include "advent_3.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(3);

    Advent3 l_advent3;
    std::cout << "Result Part One: " << l_advent3.solvePartOne("res/input_3.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent3.solvePartTwo("res/input_3.txt") << std::endl;

    return 0;
}

int Advent3::solvePartOne(const std::string &f_inputPath)
{
    std::string l_memory;
    if (readFileAsString(f_inputPath, l_memory) != 0)
    {
        return -1;
    }

    return sumValidMults(l_memory);
}

int Advent3::solvePartTwo(const std::string &f_inputPath)
{
    std::string l_memory;
    if (readFileAsString(f_inputPath, l_memory) != 0)
    {
        return -1;
    }

    return sumValidAndEnabledMults(l_memory);
}

int Advent3::readFileAsString(const std::string &f_filePath, std::string &f_outString) const
{
    std::ifstream l_file(f_filePath);

    if (!l_file)
    {
        std::cerr << "Error: Could not open file '" << f_filePath << "'" << std::endl;
        return -1; // Error
    }

    std::ostringstream l_buffer;
    l_buffer << l_file.rdbuf();

    f_outString = l_buffer.str();

    return 0; // Success
}

int Advent3::sumValidMults(const std::string &f_memory) const
{
    int l_sum = 0;

    for (int i = 0; i < f_memory.size(); i++)
    {
        int l_a;
        int l_b;
        if (isValidMult(f_memory.c_str() + i, f_memory.c_str() + f_memory.size(), l_a, l_b))
        {
            l_sum += l_a * l_b;
        }
    }

    return l_sum;
}

bool Advent3::isValidMult(const char *f_begin, const char *f_end, int &f_outA, int &f_outB) const
{
    const char *f_charPtr = f_begin;
    if ((f_end - f_charPtr) < 4)
    {
        return false;
    }

    if (std::strncmp(f_charPtr, "mul(", 4) != 0)
    {
        return false;
    }
    f_charPtr += 4;

    int l_aLength = getNumberLength(f_charPtr, f_end);
    if (l_aLength == 0)
    {
        return false;
    }
    f_outA = parseInt(f_charPtr, l_aLength);
    f_charPtr += l_aLength;

    if ((f_end - f_charPtr) < 1)
    {
        return false;
    }

    if ((*f_charPtr) != ',')
    {
        return false;
    }
    f_charPtr++;

    int l_bLength = getNumberLength(f_charPtr, f_end);
    if (l_bLength == 0)
    {
        return false;
    }
    f_outB = parseInt(f_charPtr, l_bLength);
    f_charPtr += l_bLength;

    if ((f_end - f_charPtr) < 1)
    {
        return false;
    }

    return (*f_charPtr) == ')';
}

int Advent3::getNumberLength(const char *f_begin, const char *f_end) const
{
    int l_length = 0;
    const int l_maxLength = std::min(3, static_cast<int>(f_end - f_begin));
    while ((l_length < l_maxLength) && isCharDigit(f_begin[l_length]))
    {
        l_length++;
    }

    return l_length;
}

bool Advent3::isCharDigit(const char f_digit) const
{
    return (f_digit >= '0') && (f_digit <= '9');
}

int Advent3::parseInt(const char *f_begin, const int f_size) const
{
    std::string l_temp(f_begin, f_size);
    return std::stoi(l_temp);
}

int Advent3::sumValidAndEnabledMults(const std::string &f_memory) const
{
    int l_sum = 0;
    bool l_enabled = true;
    const char *f_end = f_memory.c_str() + f_memory.size();
    for (const char *f_begin = f_memory.c_str(); f_begin < f_end; f_begin++)
    {
        int l_a;
        int l_b;
        if (l_enabled && isValidMult(f_begin, f_end, l_a, l_b))
        {
            l_sum += l_a * l_b;
        }
        else if (std::strncmp(f_begin, "do()", std::min(4, int(f_end - f_begin))) == 0)
        {
            l_enabled = true;
        }
        else if(std::strncmp(f_begin, "don't()", std::min(7, int(f_end - f_begin))) == 0)
        {
            l_enabled = false;
        }
    }

    return l_sum;
}
