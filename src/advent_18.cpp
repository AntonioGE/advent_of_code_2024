#include "advent_18.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "advent_common.hpp"

Vec g_dirTable[4] = {
    Vec{0, 1},
    Vec{-1, 0},
    Vec{0, -1},
    Vec{1, 0}};

int main()
{
    AdventCommon::printDay(18);

    Advent18 l_advent18;
    std::cout << "Result Part One: " << l_advent18.solvePartOne("res/input_18.txt") << std::endl;
    std::cout << "Result Part Two: " << l_advent18.solvePartTwo("res/input_18.txt") << std::endl;

    return 0;
}

uint64_t Advent18::solvePartOne(const std::string &f_inputPath)
{
    std::vector<Vec> l_blocks;
    if (readBlocks(f_inputPath, l_blocks) != 0)
    {
        return -1;
    }

    CharGrid l_grid(71, 71, '.');
    std::vector<Vec> l_firstBlocks(l_blocks.begin(), l_blocks.begin() + std::min(1024, static_cast<int>(l_blocks.size())));
    setBlocksOnGrid(l_grid, l_firstBlocks);
    return findMinSteps(l_grid);
}

std::string Advent18::solvePartTwo(const std::string &f_inputPath)
{
    std::vector<Vec> l_blocks;
    if (readBlocks(f_inputPath, l_blocks) != 0)
    {
        return "error";
    }

    Vec l_block = findFirstBlockinBlock(l_blocks);
    std::string l_strXY = "";
    l_strXY += std::to_string(l_block.col) + "," + std::to_string(l_block.row);
    return l_strXY;
}

int Advent18::readBlocks(const std::string &f_filePath, std::vector<Vec> &f_outBlocks) const
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        std::cerr << "Error: Unable to open '" << f_filePath << "'" << std::endl;
        return -1;
    }

    f_outBlocks.clear();

    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        std::stringstream l_ss(l_line);
        Vec l_vec;
        char l_comma;

        if (l_ss >> l_vec.col >> l_comma >> l_vec.row)
        {
            f_outBlocks.push_back(l_vec);
        }
    }

    l_file.close();

    return 0; // Success
}

void Advent18::setBlocksOnGrid(CharGrid &f_grid, const std::vector<Vec> &f_blocks) const
{
    for (const Vec &l_block : f_blocks)
    {
        f_grid(l_block) = '#';
    }
}

uint64_t Advent18::findMinSteps(CharGrid &f_grid) const
{
    const Node l_start(Vec{0, 0}, 0);
    const Vec l_end{f_grid.size.row - 1, f_grid.size.col - 1};

    NodeMap l_nodeMapUnvisited;
    l_nodeMapUnvisited[l_start.pos] = l_start;

    while (!l_nodeMapUnvisited.empty())
    {
        const Node &l_node = l_nodeMapUnvisited[findLowestScoreNodePos(l_nodeMapUnvisited)];

        if (l_node.pos != l_end)
        {
            updateNeighborsScore(l_node, f_grid, l_nodeMapUnvisited);
            f_grid(l_node.pos) = 'O';
            l_nodeMapUnvisited.erase(l_node.pos);
        }
        else
        {
            return l_node.score;
        }
    }

    return 0xFFFFFFFFFFFFFFFF;
}

Vec Advent18::findLowestScoreNodePos(const NodeMap &f_nodeMap) const
{
    Vec l_posMinNode{0, 0};
    uint64_t l_minScore = 0xFFFFFFFFFFFFFFFF;
    for (const auto &l_entry : f_nodeMap)
    {
        if (l_entry.second.score < l_minScore)
        {
            l_minScore = l_entry.second.score;
            l_posMinNode = l_entry.first;
        }
    }
    return l_posMinNode;
}

void Advent18::updateNeighborsScore(const Node f_parent, const CharGrid &f_grid, NodeMap &f_nodeMap) const
{
    for (int i = 0; i < 4; i++)
    {
        const Vec l_pos = f_parent.pos + g_dirTable[i];
        if (!f_grid.isInside(l_pos))
        {
            continue;
        }

        if (f_grid(l_pos) != '.')
        {
            continue;
        }

        const int l_score = f_parent.score + 1;
        auto l_it = f_nodeMap.find(l_pos);
        if (l_it == f_nodeMap.end())
        {
            f_nodeMap[l_pos] = Node(l_pos, l_score);
        }
        else if (l_score < l_it->second.score)
        {
            Node &l_neighbor = l_it->second;
            l_neighbor.score = l_score;
        }
    }
}

Vec Advent18::findFirstBlockinBlock(const std::vector<Vec> &f_blocks) const
{
    int l_left = 1, l_right = f_blocks.size();
    while (l_left < l_right)
    {
        int l_mid = l_left + (l_right - l_left) / 2;
        CharGrid l_grid(71, 71, '.');
        std::vector<Vec> l_firstBlocks(f_blocks.begin(), f_blocks.begin() + l_mid);
        setBlocksOnGrid(l_grid, l_firstBlocks);

        if (findMinSteps(l_grid) == 0xFFFFFFFFFFFFFFFF)
        {
            l_right = l_mid;
        }
        else
        {
            l_left = l_mid + 1;
        }
    }

    return (l_left > 1) ? f_blocks[l_left - 1] : Vec{0, 0};
}
