#include "advent_9.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "advent_common.hpp"

int main()
{
    AdventCommon::printDay(9);

    Advent9 l_advent9;
    std::cout << "Result Part One: " << l_advent9.solvePartOne("res/input_9.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent9.solvePartTwo("res/input_9.txt") << std::endl;

    return 0;
}

int64_t Advent9::solvePartOne(const std::string &f_inputPath)
{
    std::vector<char> l_disk;
    if (readFile(f_inputPath, l_disk) != 0)
    {
        return -1;
    }

    return calculateChecksum(l_disk);
}

int64_t Advent9::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<char> l_disk;
    if (readFile(f_inputPath, l_disk) != 0)
    {
        return -1;
    }

    return calcualteChecksumWhole(l_disk);
}

int Advent9::readFile(const std::string &f_filePath, std::vector<char> &f_outDisk) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outDisk.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        f_outDisk.insert(f_outDisk.end(), l_line.begin(), l_line.end());
    }

    l_file.close();

    return 0; // Success
}

int64_t Advent9::calculateChecksum(std::vector<char> &f_disk) const
{
    int64_t l_checksum = 0;

    std::vector<int> l_expDisk = expandDisk(f_disk);

    int l_freeIdxBegin = 0;
    for (int i = l_expDisk.size() - 1; i >= 0; i--)
    {
        if (l_expDisk[i] < 0)
        {
            continue;
        }

        auto l_it = std::find(l_expDisk.begin() + l_freeIdxBegin, l_expDisk.begin() + i, -1);
        if (l_it == l_expDisk.end())
        {
            break;
        }

        std::swap(l_expDisk[i], *l_it);

        l_freeIdxBegin = std::distance(l_expDisk.begin(), l_it) + 1;
    }

    for (int i = 0; (i < l_expDisk.size()) && (l_expDisk[i] != -1); i++)
    {
        l_checksum += l_expDisk[i] * i;
    }

    return l_checksum;
}

std::vector<int> Advent9::expandDisk(std::vector<char> &f_disk) const
{
    std::vector<int> l_expDisk;

    if ((f_disk.size() % 2) != 0)
    {
        f_disk.push_back('0');
    }

    for (int i = 0; i < (f_disk.size() / 2); i++)
    {
        int l_numBlocks = f_disk[i * 2] - '0';
        for (int j = 0; j < l_numBlocks; j++)
        {
            l_expDisk.push_back(i);
        }

        int l_numFree = f_disk[i * 2 + 1] - '0';
        for (int j = 0; j < l_numFree; j++)
        {
            l_expDisk.push_back(-1);
        }
    }

    return l_expDisk;
}

int64_t Advent9::calcualteChecksumWhole(std::vector<char> &f_disk) const
{
    int64_t l_checksum = 0;

    std::vector<FileData> l_expDisk = expandDiskWhole(f_disk);

    for (int i = l_expDisk.size() - 1; i >= 0; i--)
    {
        if (l_expDisk[i].id == -1)
        {
            continue;
        }

        int l_requiredSize = l_expDisk[i].size;

        auto l_lambdaIsFree = [&](const FileData &f_fileData)
        {
            return (f_fileData.id == -1) && (f_fileData.size >= l_requiredSize);
        };
        auto l_it = std::find_if(l_expDisk.begin(), l_expDisk.begin() + i, l_lambdaIsFree);
        if (l_it == l_expDisk.end())
        {
            continue;
        }

        int l_remainingSize = l_it->size - l_requiredSize;
        l_it->size = l_requiredSize;
        std::swap(l_expDisk[i], *l_it);
        if (l_remainingSize > 0)
        {
            FileData l_fileData;
            l_fileData.id = -1;
            l_fileData.size = l_remainingSize;
            l_expDisk.insert(l_it + 1, l_fileData);
            i++;
        }
    }

    for (int i = 0, l_idx = 0; i < l_expDisk.size(); i++)
    {
        if (l_expDisk[i].id != -1)
        {
            for (int j = 0; j < l_expDisk[i].size; j++)
            {
                l_checksum += l_expDisk[i].id * l_idx;
                l_idx++;
            }
        }
        else
        {
            l_idx += l_expDisk[i].size;
        }
    }

    return l_checksum;
}

std::vector<FileData> Advent9::expandDiskWhole(std::vector<char> &f_disk) const
{
    std::vector<FileData> l_expDisk;

    if ((f_disk.size() % 2) != 0)
    {
        f_disk.push_back('0');
    }

    for (int i = 0; i < (f_disk.size() / 2); i++)
    {
        int l_numBlocks = f_disk[i * 2] - '0';
        if (l_numBlocks > 0)
        {
            FileData l_fileData;
            l_fileData.id = i;
            l_fileData.size = l_numBlocks;
            l_expDisk.push_back(l_fileData);
        }

        int l_numFree = f_disk[i * 2 + 1] - '0';
        if (l_numFree > 0)
        {
            FileData l_fileData;
            l_fileData.id = -1;
            l_fileData.size = l_numFree;
            l_expDisk.push_back(l_fileData);
        }
    }

    return l_expDisk;
}
