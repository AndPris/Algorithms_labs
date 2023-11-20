#include "Random_generators.h"

int generateNumberInRange(int lowerBound, int upperBound) {
    return lowerBound + rand() % (upperBound - lowerBound + 1);
}

double generateDoubleNumberInRange(double lowerBound, double upperBound) {
    double f = (double)rand() / RAND_MAX;
    return lowerBound + f * (upperBound - lowerBound);
}