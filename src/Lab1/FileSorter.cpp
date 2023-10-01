#include "FileSorter.h"

//TODO: remove
void display(string path) {
	ifstream file(path, ios::binary);

	int number;
	int i = 0;
	while (i < 100 && file.peek() != EOF) {
		++i;
		file.read((char*)&number, sizeof(number));
		std::cout << number << " ";
	}
	std::cout << endl;

	file.close();
}


FileSorter::FileSorter(const wchar_t* file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files)
	: amount_of_supporting_files(amount_of_supporting_files) {

	this->file_to_sort_path = file_to_sort_path;

	_SYSTEM_INFO s;
	GetSystemInfo(&s);
	memory_allocation_granularity = s.dwAllocationGranularity;

	supporting_files_names = new string[amount_of_supporting_files];
	for (int i = 0; i < amount_of_supporting_files; ++i)
		supporting_files_names[i] = supporting_file_prefix + to_string(i+1) + file_extension;


	supporting_files_names_indexes = new int[amount_of_supporting_files];
	ideal_amount_of_series = new int[amount_of_supporting_files];
	amount_of_empty_series = new int[amount_of_supporting_files];
	active_supporting_files_indexes = new int[amount_of_supporting_files - 1];
	first_numbers = new int[amount_of_supporting_files];
	for (int i = 0; i < amount_of_supporting_files-1; ++i) {
		ideal_amount_of_series[i] = 1;
		amount_of_empty_series[i] = 1;
		supporting_files_names_indexes[i] = i;
	}
	ideal_amount_of_series[amount_of_supporting_files-1] = 0;
	amount_of_empty_series[amount_of_supporting_files-1] = 0;
	supporting_files_names_indexes[amount_of_supporting_files - 1] = amount_of_supporting_files - 1;
	
	level = 1;
}


void FileSorter::pre_sort() {
	const int amount_of_parts = 9;

	HANDLE file_to_sort = CreateFile(file_to_sort_path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file_to_sort == INVALID_HANDLE_VALUE) {
		throw "File Creation error";
	}

	DWORD file_size = GetFileSize(file_to_sort, NULL);
	DWORD part_size = (file_size / memory_allocation_granularity / amount_of_parts) * memory_allocation_granularity;

	HANDLE file_mapping = CreateFileMapping(file_to_sort, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (file_mapping == NULL) {
		CloseHandle(file_to_sort);
		throw "File Mapping Creation error";
	}

	for (int k = 0; k < amount_of_parts; ++k) {
		DWORD offset = k * part_size;
		DWORD part_file_size = (k == amount_of_parts - 1) ? (file_size - offset) : part_size;

		LPVOID mapped_data = MapViewOfFile(file_mapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, offset, part_file_size);
		if (mapped_data == NULL) {
			CloseHandle(file_mapping);
			CloseHandle(file_to_sort);
			throw "Map View error";
		}

		int* data = static_cast<int*>(mapped_data);
		sort(data, data + part_file_size / sizeof(int));
		UnmapViewOfFile(mapped_data);
	}

	CloseHandle(file_mapping);
	CloseHandle(file_to_sort);
}

void FileSorter::make_initial_spliting() {
	HANDLE file_to_sort = CreateFile(file_to_sort_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file_to_sort == INVALID_HANDLE_VALUE) {
		throw "File Creation error";
	}

	DWORD file_size = GetFileSize(file_to_sort, NULL);
	DWORD recorded_data_size = 0;
	DWORD part_size = 10 * memory_allocation_granularity;
	int part_counter = 0;

	HANDLE file_mapping = CreateFileMapping(file_to_sort, NULL, PAGE_READONLY, 0, 0, NULL);
	if (file_mapping == NULL) {
		CloseHandle(file_to_sort);
		throw "File Mapping Creation error";
	}

	LPVOID mapped_data = MapViewOfFile(file_mapping, FILE_MAP_READ, 0, part_counter * part_size, (part_size > file_size - part_size * part_counter ? file_size - part_size * part_counter : part_size));
	part_counter++;
	if (mapped_data == NULL) {
		CloseHandle(file_mapping);
		CloseHandle(file_to_sort);
		throw "Map View error";
	}

	int* data = static_cast<int*>(mapped_data);

	ofstream* supporting_files = new ofstream[amount_of_supporting_files - 1];
	int* last_recorded_number = new int[amount_of_supporting_files - 1];

	for (int i = 0; i < amount_of_supporting_files - 1 && recorded_data_size < file_size; ++i) {
		supporting_files[i].open(supporting_files_names[i], ios::binary);
		last_recorded_number[i] = write_series(data, supporting_files[i], part_counter, file_size, part_size, recorded_data_size, file_mapping, mapped_data);
		--amount_of_empty_series[i];
	}

	int index_of_file_to_write = 0;
	while (file_size != recorded_data_size) {
		select_supporting_file_to_write_series(index_of_file_to_write);
		if (data[(recorded_data_size - part_size * (part_counter - 1)) / sizeof(int) + 1] < last_recorded_number[index_of_file_to_write])
			last_recorded_number[index_of_file_to_write] = write_series(data, supporting_files[index_of_file_to_write], part_counter, file_size, part_size, recorded_data_size, file_mapping, mapped_data);
		else {
			last_recorded_number[index_of_file_to_write] = write_series(data, supporting_files[index_of_file_to_write], part_counter, file_size, part_size, recorded_data_size, file_mapping, mapped_data);
			if (file_size != recorded_data_size)
				last_recorded_number[index_of_file_to_write] = write_series(data, supporting_files[index_of_file_to_write], part_counter, file_size, part_size, recorded_data_size, file_mapping, mapped_data);
			else
				++amount_of_empty_series[index_of_file_to_write];
		}
	}

	for (int i = 0; i < amount_of_supporting_files - 1; ++i)
		supporting_files[i].close();

	UnmapViewOfFile(mapped_data);
	CloseHandle(file_mapping);
	CloseHandle(file_to_sort);
	delete[] supporting_files;
	delete[] last_recorded_number;
	for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
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
			++level;
			max_ideal_amount_of_series = ideal_amount_of_series[0];
			for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
				amount_of_empty_series[i] = max_ideal_amount_of_series + ideal_amount_of_series[i + 1] - ideal_amount_of_series[i];
				ideal_amount_of_series[i] = max_ideal_amount_of_series + ideal_amount_of_series[i + 1];
			}
		}
		index_of_file_to_write = 0;
	}
	--amount_of_empty_series[index_of_file_to_write];
}

int FileSorter::write_series(int* from, ofstream& destination, int& part_counter, DWORD& file_size, DWORD part_size, DWORD& recorded_data_size, HANDLE& file_mapping, LPVOID& mapped_data) {
	int current_number, previous_number = -1;
	bool run = true;
	do {
		int i = (recorded_data_size - part_size * (part_counter-1)) / sizeof(int);
		current_number = from[i];

		if (current_number < previous_number) {
			run = false;
		} else {
			destination.write((char*)&current_number, sizeof(current_number));
			previous_number = current_number;
			recorded_data_size += sizeof(int);

			if (recorded_data_size % part_size == 0) {
				LPVOID mapped_data = MapViewOfFile(file_mapping, FILE_MAP_READ, 0, part_counter * part_size, (part_size > file_size - part_size*part_counter ? file_size - part_size * part_counter : part_size));
				part_counter++;

				int* data = static_cast<int*>(mapped_data);
			}
		}

		if (file_size == recorded_data_size)
			run = false;

	} while (run);

	return previous_number; //last recorded number
}


void FileSorter::polyphase_merge_sort() {
	fstream* active_supporting_files = new fstream[amount_of_supporting_files];

	for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
		active_supporting_files[i].open(supporting_files_names[i], ios::in | ios::binary);
		active_supporting_files[i].read((char*) (first_numbers + i), sizeof(int));
	}

	do {
		int max_amount_of_merged_series = ideal_amount_of_series[amount_of_supporting_files - 2];
		amount_of_empty_series[amount_of_supporting_files - 1] = 0;
		
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].close();
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].open(supporting_files_names[supporting_files_names_indexes[amount_of_supporting_files-1]], ios::out | ios::trunc | ios::binary);

		do {
			int amount_of_active_files = 0;
			for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
				if (amount_of_empty_series[i] > 0)
					--amount_of_empty_series[i];
				else {
					active_supporting_files_indexes[amount_of_active_files] = supporting_files_names_indexes[i];
					++amount_of_active_files;
				}
			}

			if (amount_of_active_files == 0)
				++amount_of_empty_series[amount_of_supporting_files - 1];
			else
				merge_one_serie(amount_of_active_files, active_supporting_files);

			--max_amount_of_merged_series;
		} while (max_amount_of_merged_series > 0);

		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].close();
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].open(supporting_files_names[supporting_files_names_indexes[amount_of_supporting_files-1]], ios::in | ios::binary);
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files - 1]].read((char*) (first_numbers + supporting_files_names_indexes[amount_of_supporting_files - 1]), sizeof(int));

		int last_supporting_file_name_index = supporting_files_names_indexes[amount_of_supporting_files - 1];
		int amount_of_empty_series_in_last_file = amount_of_empty_series[amount_of_supporting_files - 1];
		max_amount_of_merged_series = ideal_amount_of_series[amount_of_supporting_files - 2];
		for (int i = amount_of_supporting_files - 1; i > 0; --i) {
			supporting_files_names_indexes[i] = supporting_files_names_indexes[i - 1];
			amount_of_empty_series[i] = amount_of_empty_series[i - 1];
			ideal_amount_of_series[i] = ideal_amount_of_series[i - 1] - max_amount_of_merged_series;
		}
		supporting_files_names_indexes[0] = last_supporting_file_name_index;
		amount_of_empty_series[0] = amount_of_empty_series_in_last_file;
		ideal_amount_of_series[0] = max_amount_of_merged_series;
		
		--level;

		/*for (int i = 0; i < amount_of_supporting_files; i++) {
			cout << supporting_files_names[i] << endl;
			display(supporting_files_names[i]);
			cout << "----------------------------" << endl;
		}
		cout << endl << endl;*/
	} while (level > 0);

	for (int i = 0; i < amount_of_supporting_files - 1; ++i)
		active_supporting_files[i].close();

	cout << "Result:" << endl;
	display(supporting_files_names[supporting_files_names_indexes[0]]);
	delete[] active_supporting_files;
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

int FileSorter::get_next_number(fstream& from) {
	int number;
	from.read((char*)&number, sizeof(number));
	from.seekg(-1 * sizeof(number), ios::cur);
	return number;
}


FileSorter::~FileSorter() {
	delete[] supporting_files_names;
	delete[] ideal_amount_of_series;
	delete[] amount_of_empty_series;
	delete[] active_supporting_files_indexes;
	delete[] supporting_files_names_indexes;
	delete[] first_numbers;
}