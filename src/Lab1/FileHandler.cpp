#include "FileHandler.h"


int FileHandler::generate_number_from_range(int low_border, int top_border) {
	srand(time(nullptr));

	return low_border + rand() % (top_border - low_border + 1);
}