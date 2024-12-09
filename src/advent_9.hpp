#ifndef ADVENT_9_HPP
#define ADVENT_9_HPP

#include <string>
#include <vector>
#include <cstdint>

struct FileData
{
    int id;
    int size;
};

class Advent9
{
public:
    int64_t solvePartOne(const std::string &f_inputPath);
    int64_t solvePartTwo(const std::string &f_inputPath);

private:
    int readFile(const std::string &f_filePath, std::vector<char> &f_outDisk) const;
    int64_t calculateChecksum(std::vector<char> &f_disk) const;
    std::vector<int> expandDisk(std::vector<char> &f_disk) const;
    int64_t calcualteChecksumWhole(std::vector<char> &f_disk) const;
    std::vector<FileData> expandDiskWhole(std::vector<char> &f_disk) const;
};

#endif