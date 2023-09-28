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
	start_position_of_reading = new long[amount_of_supporting_files];
	active_supporting_files_indexes = new int[amount_of_supporting_files - 1];
	for (int i = 0; i < amount_of_supporting_files-1; i++) {
		ideal_amount_of_series[i] = 1;
		amount_of_empty_series[i] = 1;
		start_position_of_reading[i] = 0;
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
		amount_of_empty_series[i]--;
	}

	int index_of_file_to_write = 0;
	while (file_to_sort.peek() != EOF) {
		select_supporting_file_to_write_series(index_of_file_to_write);
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
	int current_number;
	do {
		from.read((char*)&current_number, sizeof(current_number));
		destination.write((char*)&current_number, sizeof(current_number));
		cout << current_number << endl;
	} while (from.peek() != EOF && from.peek() >= current_number);

	return current_number; //last recorded number
}


void FileSorter::polyphase_merge_sort() {
	ifstream* active_supporting_files = new ifstream[amount_of_supporting_files - 1];

	do {
		int max_amount_of_merged_series = ideal_amount_of_series[amount_of_supporting_files - 2];
		amount_of_empty_series[amount_of_supporting_files - 1] = 0;

		ofstream merging_file(supporting_files_names[amount_of_supporting_files - 1], ios::binary);
		start_position_of_reading[amount_of_supporting_files - 1] = 0;
		for (int i = 0; i < amount_of_supporting_files - 1; i++) {
			active_supporting_files[i].open(supporting_files_names[i], ios::binary);
			active_supporting_files[i].seekg(start_position_of_reading[i]);
		}

		do {
			int amount_of_active_files = 0;
			for (int i = 0; i < amount_of_supporting_files - 1; i++) {
				if (amount_of_empty_series[i] > 0)
					amount_of_empty_series[i]--;
				else {
					active_supporting_files_indexes[amount_of_active_files] = i;
					amount_of_active_files++;
				}
			}

			if (amount_of_active_files == 0)
				amount_of_empty_series[amount_of_supporting_files - 1]++;
			else
				merge_one_serie(amount_of_active_files, active_supporting_files, merging_file);

			max_amount_of_merged_series--;
		} while (max_amount_of_merged_series > 0);
		
		merging_file.close();
		for (int i = 0; i < amount_of_supporting_files-1; i++)
			active_supporting_files[i].close();

		string last_supporting_file_name = supporting_files_names[amount_of_supporting_files - 1];
		int amount_of_empty_series_in_last_file = amount_of_empty_series[amount_of_supporting_files - 1];
		max_amount_of_merged_series = ideal_amount_of_series[amount_of_supporting_files - 2];
		long last_file_start_position = start_position_of_reading[amount_of_supporting_files - 1];
		for (int i = amount_of_supporting_files - 1; i > 0; i--) {
			supporting_files_names[i] = supporting_files_names[i - 1];
			amount_of_empty_series[i] = amount_of_empty_series[i - 1];
			ideal_amount_of_series[i] = ideal_amount_of_series[i - 1] - max_amount_of_merged_series;
			start_position_of_reading[i] = start_position_of_reading[i - 1];
		}
		supporting_files_names[0] = last_supporting_file_name;
		amount_of_empty_series[0] = amount_of_empty_series_in_last_file;
		ideal_amount_of_series[0] = max_amount_of_merged_series;
		start_position_of_reading[0] = last_file_start_position;
		level--;
	} while (level > 0);
	cout << "Result:" << endl;
	display(supporting_files_names[0]);
	delete[] active_supporting_files;
}

void FileSorter::merge_one_serie(int amount_of_active_files, ifstream* active_supporting_files, ofstream& output_file) {
	do {
		int i = 0, index_of_file_with_min_element = 0, min = active_supporting_files[active_supporting_files_indexes[0]].peek();
		while (i < amount_of_active_files - 1) {
			i++;
			int current_element = active_supporting_files[active_supporting_files_indexes[i]].peek();
			if (current_element < min) {
				min = current_element;
				index_of_file_with_min_element = i;
			}
		}
		active_supporting_files[active_supporting_files_indexes[index_of_file_with_min_element]].read((char*)&min, sizeof(min));
		start_position_of_reading[active_supporting_files_indexes[index_of_file_with_min_element]] = active_supporting_files[active_supporting_files_indexes[index_of_file_with_min_element]].tellg();
		output_file.write((char*)&min, sizeof(min));

		if (active_supporting_files[index_of_file_with_min_element].peek() < min) {
			active_supporting_files_indexes[index_of_file_with_min_element] = active_supporting_files_indexes[amount_of_active_files - 1];
			amount_of_active_files--;
		}
	} while (amount_of_active_files > 0);
}

FileSorter::~FileSorter() {
	delete[] supporting_files_names;
	delete[] ideal_amount_of_series;
	delete[] amount_of_empty_series;
	delete[] active_supporting_files_indexes;
	delete[] start_position_of_reading;
}