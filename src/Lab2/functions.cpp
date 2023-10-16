#include "functions.h"


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

void copy(int** dest, int** src, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            dest[i][j] = src[i][j];
    }
}