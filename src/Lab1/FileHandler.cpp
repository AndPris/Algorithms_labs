#include "FileHandler.h"


FileHandler::FileHandler(int size_of_initial_file_in_mb, int amount_of_supporting_files) : size_of_initial_file_in_mb(size_of_initial_file_in_mb), amount_of_suporting_files(amount_of_suporting_files) {
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