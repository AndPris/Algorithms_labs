#pragma once

#include <ctime>
#include <random>
#include "MemoryHandler.h"
using namespace std;


class PuzzleCreator {
    int** allocate_memory_for_puzzle(int puzzle_size);
    void fill_puzzle_with_zeros(int **puzzle, int puzzle_size);

    int generate_coords(int **puzzle, int puzzle_size);
    int generate_number_in_range(int low, int top);
public:
    int** create_puzzle(int puzzle_size);
};