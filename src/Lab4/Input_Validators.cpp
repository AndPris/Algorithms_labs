#include "Input_Validators.h"

int inputPositiveNumberInRange(int low, int top) {
    int number;
    string input;
    bool repeat;
    do {
        repeat = false;
        getline(cin, input);
        if (!isNumber(input) || (input[0] == '0' && input.length() != 1)) {
            cout << "Invalid data, input positive integer number, please." << endl;
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
bool isNumber(const string& input) {
    for (char ch : input) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}