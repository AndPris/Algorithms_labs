#include "FileCreator.h"


FileCreator::FileCreator(const wchar_t* initial_file_path, int size_of_initial_file_in_mb) : size_of_initial_file_in_mb(size_of_initial_file_in_mb) {
	this->initial_file_path = initial_file_path;
}

void FileCreator::create_initial_file() const{
	ofstream initial_file(initial_file_path, ios::binary);

	int amount_of_numbers = 21;//size_of_initial_file_in_mb * 1024 * 1024 / sizeof(int);
	for (int i = 0; i < amount_of_numbers; ++i) {
		int random_number = amount_of_numbers - i;//rand();
		initial_file.write((char*)&random_number, sizeof(int));
	}

	initial_file.close();
}

const wchar_t* FileCreator::get_initial_file_path() const {
	return initial_file_path;
}