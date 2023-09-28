#include "FileHandler.h"


FileHandler::FileHandler(string initial_file_path, int size_of_initial_file_in_mb) : size_of_initial_file_in_mb(size_of_initial_file_in_mb) {
	this->initial_file_path = initial_file_path;
}

void FileHandler::create_initial_file() const{
	RandomGenerator generator;
	ofstream initial_file(initial_file_path, ios::binary);

	int amount_of_numbers = size_of_initial_file_in_mb;// TODO: size_of_initial_file_in_mb * 1024 / sizeof(int);
	for (int i = 0; i < amount_of_numbers; i++) {
		int random_number = amount_of_numbers - i;//TODO generator.generate_number_from_range(1, amount_of_numbers);
		initial_file.write((char*)&random_number, sizeof(random_number));
	}

	initial_file.close();
}

void FileHandler::display_initial_file() const{
	ifstream initial_file(initial_file_path, ios::binary);

	int number;
	while (initial_file.peek() != EOF) {
		initial_file.read((char*)&number, sizeof(number));
		cout << number << " ";
	}
	cout << endl;

	initial_file.close();
}

string FileHandler::get_initial_file_path() const {
	return initial_file_path;
}