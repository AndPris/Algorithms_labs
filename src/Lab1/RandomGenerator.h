#pragma once

#include <random>

class RandomGenerator
{
public:
	RandomGenerator();

	int generate_number_from_range(int low_border, int top_border);
};

