#include "FileHandler.h"


FileHandler::FileHandler(int size_of_initial_file_in_mb, int amount_of_supporting_files) : size_of_initial_file_in_mb(size_of_initial_file_in_mb), amount_of_suporting_files(amount_of_suporting_files) {
	path_to_folder = "x64/Debug/";
	file_extension = ".bin";
	initial_file_name = path_to_folder + "initial" + file_extension;
	supporting_file_prefix = path_to_folder + "supporting_";

	supporting_files_names = new string[amount_of_suporting_files];
	for (int i = 0; i < amount_of_suporting_files; i++)
		supporting_files_names[i] = supporting_file_prefix + to_string(i) + file_extension;

}

void FileHandler::create_initial_file() {
	RandomGenerator generator;
	ofstream initial_file(initial_file_name, ios::binary);

	int amount_of_numbers = size_of_initial_file_in_mb;// TODO: size_of_initial_file_in_mb * 1024 / sizeof(int);
	for (int i = 0; i < amount_of_numbers; i++) {
		int random_number = generator.generate_number_from_range(1, amount_of_numbers);
		initial_file.write((char*)&random_number, sizeof(random_number));
	}

	initial_file.close();
}

void FileHandler::display_initial_file() {
	ifstream initial_file(initial_file_name, ios::binary);

	int number;
	while (initial_file.peek() != EOF) {
		initial_file.read((char*)&number, sizeof(number));
		cout << number << " ";
	}
	cout << endl;

	initial_file.close();
}

FileHandler::~FileHandler() {
	delete[] supporting_files_names;
}