#include "FileHandler.h"


int FileHandler::generate_number_from_range(int low_border, int top_border) {
	srand(time(nullptr));

	return low_border + rand() % (top_border - low_border + 1);
}


FileHandler::FileHandler(int amount_of_supporting_files) : amount_of_suporting_files(amount_of_suporting_files) {
	file_extension = ".bin";
	initial_file_name = "initial" + file_extension;
	supporting_file_prefix = "supporting_";

	supporting_files_names = new string[amount_of_suporting_files];
	for (int i = 0; i < amount_of_suporting_files; i++)
		supporting_files_names[i] = supporting_file_prefix + to_string(i) + file_extension;


}

FileHandler::~FileHandler() {
	delete[] supporting_files_names;
}