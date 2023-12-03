#include "Random_generators.h"

int generateNumberInRange(int lowerBound, int upperBound) {
    return lowerBound + rand() % (upperBound - lowerBound + 1);
}