#include "MemoryHandler.h"

int **MemoryHandler::allocate_memory(int amount_of_rows, int amount_of_cols) {
    int **matrix = new int* [amount_of_rows];
    for(int i = 0; i < amount_of_rows; ++i)
        matrix[i] = new int[amount_of_cols];
    return matrix;
}

void MemoryHandler::delete_memory(int **from, int amount_of_rows) {
    for(int i = 0; i < amount_of_rows; ++i)
        delete[] from[i];
    delete[] from;
}