#include "random_generators.h"

int generate_number_in_range(int low, int top) {
	return low + rand() % (top - low + 1);
}

char* generate_string(int length) {
	string symbols = "abcdefghijklmnopqrstuvwxyz";

	char* result = new char[length+1];
	for (int i = 0; i < length; ++i)
		result[i] = symbols[generate_number_in_range(0, symbols.length())];
	result[length] = '\0';

	return result;
}