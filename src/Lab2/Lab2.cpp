#include "PuzzleCreator.h"
#include "PuzzleSolver.h"
#include <ctime>
#include <iomanip>
#include <string>

int input_positive_number_in_range(int low, int top);
bool is_number(const string& input);
void display(int** matrix, int size);

int main() {
    const int PUZZLE_SIZE = 3;
    const int LIMIT = 26;
    PuzzleCreator creator;
    PuzzleSolver solver;
    int run;
    clock_t beginning_of_searching, end_of_searching;

    do {
        int** puzzle = creator.create_puzzle(PUZZLE_SIZE);
        cout << "Puzzle:" << endl;
        display(puzzle, PUZZLE_SIZE);

        try {
            beginning_of_searching = clock();
            int** result = solver.LDFS_solve(puzzle, PUZZLE_SIZE, LIMIT);
            end_of_searching = clock();

            cout << "LDFS solution:" << endl;
            display(result, PUZZLE_SIZE);
            cout << "LDFS searching took " << fixed << double(end_of_searching - beginning_of_searching) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;
        }
        catch (const char* er) {
            cout << er << endl;
            end_of_searching = clock();
            cout << "LDFS searching took " << fixed << double(end_of_searching - beginning_of_searching) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;
        }

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

        cout << "Enter 0 to stop program or 1 to run it again" << endl;
        run = input_positive_number_in_range(0, 1);
    } while (run);
    return 0;
}

int input_positive_number_in_range(int low, int top) {
    int number;
    string input;
    bool repeat;
    do {
        repeat = false;
        getline(cin, input);
        if (!is_number(input)) {
            cout << "Invalid data, input integer number, please." << endl;
            repeat = true;
            continue;
        }

        number = stoi(input);
        if (number < low || number > top) {
            cout << "Number must be from " << low << " to " << top << endl;
            repeat = true;
        }
    } while (repeat);
    return number;
}
bool is_number(const string& input) {
    for (char ch : input) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}
void display(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << "--------------------------" << endl;
}