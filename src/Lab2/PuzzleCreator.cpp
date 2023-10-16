#include "PuzzleCreator.h"

int **PuzzleCreator::create_puzzle(int puzzle_size) {
    srand(time(nullptr));

    int **puzzle = allocate_memory_for_puzzle(puzzle_size);
    fill_puzzle_with_zeros(puzzle, puzzle_size);

    for(int i = 1; i < puzzle_size*puzzle_size; ++i) {
        int coord = generate_coords(puzzle, puzzle_size);
        puzzle[coord/3][coord%3] = i;
    }

    return puzzle;
}
int** PuzzleCreator::allocate_memory_for_puzzle(int puzzle_size) {
    MemoryHandler handler;
    return handler.allocate_memory(puzzle_size, puzzle_size);
}
void PuzzleCreator::fill_puzzle_with_zeros(int **puzzle, int puzzle_size) {
    for(int i = 0; i < puzzle_size; ++i) {
        for(int j = 0; j < puzzle_size; ++j)
            puzzle[i][j] = 0;
    }
}
int PuzzleCreator::generate_coords(int **puzzle, int puzzle_size) {
    int coord;

    do {
        coord = generate_number_in_range(0, puzzle_size*puzzle_size-1);
    } while(puzzle[coord/3][coord%3] != 0);

    return coord;
}
int PuzzleCreator::generate_number_in_range(int low, int top) {
    return low + rand() % (top-low+1);
}