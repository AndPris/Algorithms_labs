#pragma once

#include <string>
#include <iostream>
using namespace std;

int input_positive_number_in_range(int low, int top);
bool is_number(const string& input);
void display(int** matrix, int size);

void copy(int **dest, int** src, int size);