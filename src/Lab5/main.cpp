#include <iostream>
#include "random_generators.h"
using namespace std;

int main() {
	srand(time(nullptr));

	cout << generateNumberInRange(3, 10) << endl;
	return 0;
}