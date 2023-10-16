#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include "MemoryHandler.h"
using namespace std;

class PuzzleSolver {
    class Node {
        #define INITIAL 0
        #define UP 1
        #define DOWN 2
        #define LEFT 3
        #define RIGHT 4

        struct Coords {
            int row, col;
        };
        
        int** state;
        int size;
        Coords empty_cell_coords;
        int depth;
        int action;

        void copy(int **src);
        Coords find_coords_of_empty_cell() const;
        
        bool is_empty_cell_in_top_row() const;
        bool is_empty_cell_in_bottom_row() const;
        bool is_empty_cell_in_left_col() const;
        bool is_empty_cell_in_right_col() const;

        Node move_up();
        Node move_down();
        Node move_left();
        Node move_right();
        void swap(int &first_number, int &second_number);
    public:
        Node() = default;
        Node(int **puzzle, int puzzle_size, int depth, int action);
        Node(Node&& obj);
        Node(const Node& obj);
        Node& operator=(Node&& obj);

        int get_amount_of_successors() const;

        Node* expand();
        bool is_solution() const;

        int** get_state();
        int get_depth() const;
        int manhattan_distance() const;

        bool operator==(const Node& obj) const;

        ~Node();
    };

    bool is_solvable(int **puzzle, int size) const;
    int* create_elements_array(int **puzzle, int size) const;
    int count_inversions(int *elements, int size) const;

    int** _LDFS_solve(Node &node, int limit, bool &is_cutoff, bool &is_failure);

    bool contains(vector<Node> &container, const Node& obj) const;
public:
    int** LDFS_solve(int** puzzle, int puzzle_size, int limit);
    int** A_star(int** puzzle, int puzzle_size);
};