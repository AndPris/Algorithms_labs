#include "FileSorter.h"

FileSorter::FileSorter(string file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files)
	: amount_of_suporting_files(amount_of_suporting_files) {

	this->file_to_sort_path = file_to_sort_path;
	supporting_files_names = new string[amount_of_suporting_files];
	for (int i = 0; i < amount_of_suporting_files; i++)
		supporting_files_names[i] = supporting_file_prefix + to_string(i) + file_extension;
	
}

FileSorter::~FileSorter() {
	delete[] supporting_files_names;
}