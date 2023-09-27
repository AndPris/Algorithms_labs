#include "RandomGenerator.h"


RandomGenerator::RandomGenerator() {
	srand(time(nullptr));
}

int RandomGenerator::generate_number_from_range(int low_border, int top_border) {
	return low_border + rand() % (top_border - low_border + 1);
}