#include "PuzzleCreator.h"
#include "PuzzleSolver.h"
#include <ctime>
#include <iomanip>

int main() {
    const int PUZZLE_SIZE = 3;
    const int LIMIT = 26;
    PuzzleCreator creator;
    PuzzleSolver solver;
    int run;
    clock_t beginning_of_searching, end_of_searching;

    do {
        /*int** puzzle{ new int*[PUZZLE_SIZE] {
                            new int [PUZZLE_SIZE] {1, 0, 2},
                            new int [PUZZLE_SIZE] {3, 4, 5},
                            new int [PUZZLE_SIZE] {6, 7, 8}}};*/

        int** puzzle = creator.create_puzzle(PUZZLE_SIZE);
       
        cout << "Puzzle:" << endl;
        display(puzzle, PUZZLE_SIZE);

        try {
            beginning_of_searching = clock();
            int** result = solver.A_star(puzzle, PUZZLE_SIZE);
            end_of_searching = clock();

            cout << "A* solution:" << endl;
            display(result, PUZZLE_SIZE);
            cout << "A* searching took " << fixed << double(end_of_searching - beginning_of_searching) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;
        }
        catch (const char* er) {
            cout << er << endl;
            end_of_searching = clock();
            cout << "A* searching took " << fixed << double(end_of_searching - beginning_of_searching) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;
        }

        try {
            beginning_of_searching = clock();
            int **result = solver.LDFS_solve(puzzle, PUZZLE_SIZE, LIMIT);
            end_of_searching = clock();
        
            cout<<"LDFS solution:"<<endl;
            display(result, PUZZLE_SIZE);
            cout << "LDFS searching took " << fixed << double(end_of_searching - beginning_of_searching) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;
        } catch (const char *er) {
            cout << er << endl;
            end_of_searching = clock();
            cout << "LDFS searching took " << fixed << double(end_of_searching - beginning_of_searching) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;
        }

        cout << "Enter 0 to stop program or 1 to run it again" << endl;
        run = input_positive_number_in_range(0, 1);
    } while (run);
    return 0;
}
