#include "FileHandler.h"


FileHandler::FileHandler(const wchar_t* initial_file_path, int size_of_initial_file_in_mb) : size_of_initial_file_in_mb(size_of_initial_file_in_mb) {
	this->initial_file_path = initial_file_path;
}

void FileHandler::create_initial_file() const{
	ofstream initial_file(initial_file_path, ios::binary);

	int amount_of_numbers = size_of_initial_file_in_mb * 1024 * 1024 / sizeof(int);
	for (int i = 0; i < amount_of_numbers; ++i) {
		int random_number = rand();
		initial_file.write((char*)&random_number, sizeof(int));
	}

	initial_file.close();
}

const wchar_t* FileHandler::get_initial_file_path() const {
	return initial_file_path;
}