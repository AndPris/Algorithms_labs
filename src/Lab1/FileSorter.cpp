#include "FileSorter.h"

//TODO: remove
void display(string path) {
	ifstream file(path, ios::binary);

	int number;
	while (file.peek() != EOF) {
		file.read((char*)&number, sizeof(number));
		std::cout << number << " ";
	}
	std::cout << endl;

	file.close();
}


FileSorter::FileSorter(string file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files)
	: amount_of_supporting_files(amount_of_supporting_files) {

	this->file_to_sort_path = file_to_sort_path;

	supporting_files_names = new string[amount_of_supporting_files];
	for (int i = 0; i < amount_of_supporting_files; i++)
		supporting_files_names[i] = supporting_file_prefix + to_string(i+1) + file_extension;

	ideal_amount_of_series = new int[amount_of_supporting_files];
	amount_of_empty_series = new int[amount_of_supporting_files];
	for (int i = 0; i < amount_of_supporting_files-1; i++) {
		ideal_amount_of_series[i] = 1;
		amount_of_empty_series[i] = 1;
	}
	ideal_amount_of_series[amount_of_supporting_files-1] = 0;
	amount_of_empty_series[amount_of_supporting_files-1] = 0;
	level = 1;
}

void FileSorter::make_initial_spliting() {
	ifstream file_to_sort(file_to_sort_path, ios::binary);
	ofstream* supporting_files = new ofstream[amount_of_supporting_files - 1];
	int* last_recorded_number = new int[amount_of_supporting_files - 1];

	for (int i = 0; i < amount_of_supporting_files - 1 && file_to_sort.peek() != EOF; i++) {
		supporting_files[i].open(supporting_files_names[i], ios::binary);
		last_recorded_number[i] = write_series(file_to_sort, supporting_files[i]);
	}

	int index_of_file_to_write = 0;
	while (file_to_sort.peek() != EOF) {
		select_supporting_file_to_write_series(index_of_file_to_write);
		cout << "j = " << index_of_file_to_write << endl;
		if (file_to_sort.peek() < last_recorded_number[index_of_file_to_write])
			last_recorded_number[index_of_file_to_write] = write_series(file_to_sort, supporting_files[index_of_file_to_write]);
		else {
			last_recorded_number[index_of_file_to_write] = write_series(file_to_sort, supporting_files[index_of_file_to_write]);
			if (file_to_sort.peek() != EOF)
				last_recorded_number[index_of_file_to_write] = write_series(file_to_sort, supporting_files[index_of_file_to_write]);
			else
				amount_of_empty_series[index_of_file_to_write]++;
		}
	}

	for (int i = 0; i < amount_of_supporting_files - 1; i++)
		supporting_files[i].close();

	file_to_sort.close();
	delete[] supporting_files;
	delete[] last_recorded_number;
	for (int i = 0; i < amount_of_supporting_files - 1; i++) {
		cout << "File " << i + 1 << ":\n";
		display(supporting_files_names[i]);
		cout << "------------------------" << endl;
	}
}

void FileSorter::select_supporting_file_to_write_series(int& index_of_file_to_write) {
	int max_ideal_amount_of_series;
	if (amount_of_empty_series[index_of_file_to_write] < amount_of_empty_series[index_of_file_to_write + 1])
		index_of_file_to_write++;
	else {
		if (amount_of_empty_series[index_of_file_to_write] == 0) {
			level++;
			max_ideal_amount_of_series = ideal_amount_of_series[0];
			for (int i = 0; i < amount_of_supporting_files - 1; i++) {
				amount_of_empty_series[i] = max_ideal_amount_of_series + ideal_amount_of_series[i + 1] - ideal_amount_of_series[i];
				ideal_amount_of_series[i] = max_ideal_amount_of_series + ideal_amount_of_series[i + 1];
			}
		}
		index_of_file_to_write = 0;
	}
	amount_of_empty_series[index_of_file_to_write]--;
}

int FileSorter::write_series(ifstream& from, ofstream& destination) {
	if (from.peek() == EOF)
		return -1;

	int current_number;
	do {
		from.read((char*)&current_number, sizeof(current_number));
		destination.write((char*)&current_number, sizeof(current_number));
		cout << current_number << endl;
	} while (from.peek() != EOF && from.peek() >= current_number);

	return current_number; //last recorded number
}

FileSorter::~FileSorter() {
	delete[] supporting_files_names;
	delete[] ideal_amount_of_series;
	delete[] amount_of_empty_series;
}