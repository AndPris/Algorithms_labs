#include "FileSorter.h"

FileSorter::FileSorter(Reader* data, string file_extension, string supporting_file_prefix, int amount_of_supporting_files, string result_file_name)
	: amount_of_supporting_files(amount_of_supporting_files), result_file_name(result_file_name) {

	data_to_sort = data;

	init_memory_granularity();
	create_supporting_files_names(supporting_file_prefix, file_extension);
	init_files_data();

	level = 1;

	remove(result_file_name.c_str());
}
void FileSorter::init_memory_granularity() {
	_SYSTEM_INFO s;
	GetSystemInfo(&s);
	memory_allocation_granularity = s.dwAllocationGranularity;
	part_size_in_granularity = 10 * 1024 * 1024 / memory_allocation_granularity;
}
void FileSorter::create_supporting_files_names(string prefix, string extension) {
	supporting_files_names = new string[amount_of_supporting_files];
	for (int i = 0; i < amount_of_supporting_files; ++i)
		supporting_files_names[i] = prefix + to_string(i + 1) + extension;
}
void FileSorter::init_files_data() {
	supporting_files_names_indexes = new int[amount_of_supporting_files];
	ideal_amount_of_series = new int[amount_of_supporting_files];
	amount_of_empty_series = new int[amount_of_supporting_files];
	first_numbers = new int[amount_of_supporting_files];
	active_supporting_files_indexes = new int[amount_of_supporting_files - 1];

	for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
		ideal_amount_of_series[i] = 1;
		amount_of_empty_series[i] = 1;
		supporting_files_names_indexes[i] = i;
	}

	ideal_amount_of_series[amount_of_supporting_files - 1] = 0;
	amount_of_empty_series[amount_of_supporting_files - 1] = 0;
	supporting_files_names_indexes[amount_of_supporting_files - 1] = amount_of_supporting_files - 1;
}

void FileSorter::pre_sort() {
	const int part_size_in_mb = 10;

	while (!data_to_sort->is_end()) {
		int *begin, *end;
		data_to_sort->read_range(begin, end, part_size_in_mb);
		sort(begin, end);
	}

	data_to_sort->open_from_beggining();
}

void FileSorter::make_initial_spliting() {
	ofstream* supporting_files = new ofstream[amount_of_supporting_files - 1];
	int* last_recorded_number = new int[amount_of_supporting_files - 1];

	for (int i = 0; i < amount_of_supporting_files - 1 && !data_to_sort->is_end(); ++i) {
		supporting_files[i].open(supporting_files_names[i], ios::binary);
		last_recorded_number[i] = write_series(data_to_sort, supporting_files[i]);
		--amount_of_empty_series[i];
	}

	int index_of_file_to_write = 0;
	while (!data_to_sort->is_end()) {
		select_supporting_file_to_write_series(index_of_file_to_write);
		bool is_series_concat = data_to_sort->peek() > last_recorded_number[index_of_file_to_write];
		last_recorded_number[index_of_file_to_write] = write_series(data_to_sort, supporting_files[index_of_file_to_write]);
		
		if (!is_series_concat)
			continue;

		if (!data_to_sort->is_end())
			last_recorded_number[index_of_file_to_write] = write_series(data_to_sort, supporting_files[index_of_file_to_write]);
		else
			++amount_of_empty_series[index_of_file_to_write];
	}

	for (int i = 0; i < amount_of_supporting_files - 1; ++i)
		supporting_files[i].close();

	delete[] supporting_files;
	delete[] last_recorded_number;
}

void FileSorter::select_supporting_file_to_write_series(int& index_of_file_to_write) {
	int max_ideal_amount_of_series;

	if (amount_of_empty_series[index_of_file_to_write] < amount_of_empty_series[index_of_file_to_write + 1]) {
		index_of_file_to_write++;
		--amount_of_empty_series[index_of_file_to_write];
		return;
	}

	if (amount_of_empty_series[index_of_file_to_write] == 0) {
		++level;
		max_ideal_amount_of_series = ideal_amount_of_series[0];
		for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
			amount_of_empty_series[i] = max_ideal_amount_of_series + ideal_amount_of_series[i + 1] - ideal_amount_of_series[i];
			ideal_amount_of_series[i] = max_ideal_amount_of_series + ideal_amount_of_series[i + 1];
		}
	}

	index_of_file_to_write = 0;
	--amount_of_empty_series[index_of_file_to_write];
}

int FileSorter::write_series(Reader* from, ofstream& destination) {
	int current_number;
	do {
		current_number = from->read();
		destination.write((char*)&current_number, sizeof(current_number));
	} while (from->peek() >= current_number && !from->is_end());
	return current_number; //last recorded number
}


void FileSorter::polyphase_merge_sort() {
	pre_sort();
	make_initial_spliting();

	fstream* active_supporting_files = new fstream[amount_of_supporting_files];

	for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
		active_supporting_files[i].open(supporting_files_names[i], ios::in | ios::binary);
		active_supporting_files[i].read((char*) (first_numbers + i), sizeof(int));
	}

	do {
		merge_series_from_level(active_supporting_files);

		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].close();
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].open(supporting_files_names[supporting_files_names_indexes[amount_of_supporting_files-1]], ios::in | ios::binary);
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].read((char*) (first_numbers + supporting_files_names_indexes[amount_of_supporting_files - 1]), sizeof(int));

		shift_suppotring_files_indexes();
		
		--level;
	} while (level > 0);

	for (int i = 0; i < amount_of_supporting_files; ++i)
		active_supporting_files[i].close();

	rename_sorted_file();
	delete_supporting_files();

	delete[] active_supporting_files;
}

void FileSorter::merge_series_from_level(fstream* active_supporting_files) {
	int max_amount_of_merged_series = ideal_amount_of_series[amount_of_supporting_files - 2];
	amount_of_empty_series[amount_of_supporting_files - 1] = 0;

	active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].close();
	active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].open(supporting_files_names[supporting_files_names_indexes[amount_of_supporting_files - 1]], ios::out | ios::trunc | ios::binary);

	do {
		int amount_of_active_files = calculate_amount_of_active_files();

		if (amount_of_active_files == 0)
			++amount_of_empty_series[amount_of_supporting_files - 1];
		else
			merge_one_serie(amount_of_active_files, active_supporting_files);

		--max_amount_of_merged_series;
	} while (max_amount_of_merged_series > 0);
}

int FileSorter::calculate_amount_of_active_files() {
	int amount_of_active_files = 0;

	for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
		if (amount_of_empty_series[i] > 0)
			--amount_of_empty_series[i];
		else {
			active_supporting_files_indexes[amount_of_active_files] = supporting_files_names_indexes[i];
			++amount_of_active_files;
		}
	}

	return amount_of_active_files;
}
void FileSorter::shift_suppotring_files_indexes() {
	int last_supporting_file_name_index = supporting_files_names_indexes[amount_of_supporting_files - 1];
	int amount_of_empty_series_in_last_file = amount_of_empty_series[amount_of_supporting_files - 1];
	int max_amount_of_merged_series = ideal_amount_of_series[amount_of_supporting_files - 2];
	
	for (int i = amount_of_supporting_files - 1; i > 0; --i) {
		supporting_files_names_indexes[i] = supporting_files_names_indexes[i - 1];
		amount_of_empty_series[i] = amount_of_empty_series[i - 1];
		ideal_amount_of_series[i] = ideal_amount_of_series[i - 1] - max_amount_of_merged_series;
	}
	
	supporting_files_names_indexes[0] = last_supporting_file_name_index;
	amount_of_empty_series[0] = amount_of_empty_series_in_last_file;
	ideal_amount_of_series[0] = max_amount_of_merged_series;
}
void FileSorter::rename_sorted_file() {
	rename(supporting_files_names[supporting_files_names_indexes[0]].c_str(), result_file_name.c_str());
}
void FileSorter::delete_supporting_files() {
	for (int i = 0; i < amount_of_supporting_files; i++)
		remove(supporting_files_names[i].c_str());
}

void FileSorter::merge_one_serie(int amount_of_active_files, fstream* active_supporting_files) {	
	do {
		int i = 0, index_of_file_with_min_element = 0, min = first_numbers[active_supporting_files_indexes[0]];
		while (i < amount_of_active_files - 1) {
			++i;
			int current_element = first_numbers[active_supporting_files_indexes[i]];
			if (current_element < min) {
				min = current_element;
				index_of_file_with_min_element = i;
			}
		}
		active_supporting_files[active_supporting_files_indexes[index_of_file_with_min_element]].read((char*) (first_numbers + active_supporting_files_indexes[index_of_file_with_min_element]), sizeof(int));
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files-1]].write((char*)&min, sizeof(min));

		if (first_numbers[active_supporting_files_indexes[index_of_file_with_min_element]] < min || active_supporting_files[active_supporting_files_indexes[index_of_file_with_min_element]].eof()) {
			--amount_of_active_files;
			active_supporting_files_indexes[index_of_file_with_min_element] = active_supporting_files_indexes[amount_of_active_files];
		}
	} while (amount_of_active_files > 0);
}

void FileSorter::display_sorted_file() {
	ifstream file(result_file_name, ios::binary);

	const int amount_of_displayed_numbers = 5;

	for (int i = 0; i < amount_of_displayed_numbers; ++i) {
		int number;
		file.read((char*)&number, sizeof(number));
		cout << number << " ";
	}

	file.seekg(-1 * sizeof(int) * amount_of_displayed_numbers, ios::end);
	cout << "... ";

	for (int i = 0; i < amount_of_displayed_numbers; ++i) {
		int number;
		file.read((char*)&number, sizeof(number));
		cout << number << " ";
	}
	cout << endl;
	file.close();
}

FileSorter::~FileSorter() {
	delete[] supporting_files_names;
	delete[] ideal_amount_of_series;
	delete[] amount_of_empty_series;
	delete[] active_supporting_files_indexes;
	delete[] supporting_files_names_indexes;
	delete[] first_numbers;
}