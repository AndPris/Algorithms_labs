#pragma once

class MemoryHandler {
public:
    int** allocate_memory(int amount_of_rows, int amount_of_cols);
    void delete_memory(int **from, int amount_of_rows);
};
