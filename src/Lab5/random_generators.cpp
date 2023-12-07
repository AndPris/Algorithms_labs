#include "Random_generators.h"

int generateNumberInRange(int lowerBound, int upperBound) {
    if (upperBound < lowerBound) {
        int temp = lowerBound;
        lowerBound = upperBound;
        upperBound = temp;
    }

    return lowerBound + rand() % (upperBound - lowerBound + 1);
}