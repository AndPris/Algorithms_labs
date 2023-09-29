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

	supporting_files_names = new string[amount_of_supporting_files];
	for (int i = 0; i < amount_of_supporting_files; ++i)
		supporting_files_names[i] = supporting_file_prefix + to_string(i+1) + file_extension;


	supporting_files_names_indexes = new int[amount_of_supporting_files];
	ideal_amount_of_series = new int[amount_of_supporting_files];
	amount_of_empty_series = new int[amount_of_supporting_files];
	active_supporting_files_indexes = new int[amount_of_supporting_files - 1];
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
	_SYSTEM_INFO s;
	GetSystemInfo(&s);

	const int amount_of_parts = 9;

	HANDLE test_file = CreateFile(file_to_sort_path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (test_file == INVALID_HANDLE_VALUE) {
		throw "File Creation error";
	}

	DWORD file_size = GetFileSize(test_file, NULL);
	DWORD part_size = (file_size / s.dwAllocationGranularity / amount_of_parts) * s.dwAllocationGranularity;

	HANDLE file_mapping = CreateFileMapping(test_file, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (file_mapping == NULL) {
		CloseHandle(test_file);
		throw "File Mapping Creation error";
	}

	for (int k = 0; k < file_size / part_size; ++k) {
		DWORD offset = k * part_size;
		DWORD part_file_size = (k == amount_of_parts - 1) ? (file_size - offset) : part_size;

		LPVOID mapped_data = MapViewOfFile(file_mapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, offset, part_file_size);
		if (mapped_data == NULL) {
			CloseHandle(file_mapping);
			CloseHandle(test_file);
			throw "Map View error";
		}

		int* data = static_cast<int*>(mapped_data);
		sort(data, data + part_file_size / sizeof(int));
		UnmapViewOfFile(mapped_data);
	}

	CloseHandle(file_mapping);
	CloseHandle(test_file);
}

void FileSorter::make_initial_spliting() {
	fstream file_to_sort(file_to_sort_path, ios::in | ios::binary);
	ofstream* supporting_files = new ofstream[amount_of_supporting_files - 1];
	int* last_recorded_number = new int[amount_of_supporting_files - 1];

	for (int i = 0; i < amount_of_supporting_files - 1 && file_to_sort.peek() != EOF; ++i) {
		supporting_files[i].open(supporting_files_names[i], ios::binary);
		last_recorded_number[i] = write_series(file_to_sort, supporting_files[i]);
		--amount_of_empty_series[i];
	}

	int index_of_file_to_write = 0;
	while (file_to_sort.peek() != EOF) {
		select_supporting_file_to_write_series(index_of_file_to_write);
		if (get_next_number(file_to_sort) < last_recorded_number[index_of_file_to_write])
			last_recorded_number[index_of_file_to_write] = write_series(file_to_sort, supporting_files[index_of_file_to_write]);
		else {
			last_recorded_number[index_of_file_to_write] = write_series(file_to_sort, supporting_files[index_of_file_to_write]);
			if (file_to_sort.peek() != EOF)
				last_recorded_number[index_of_file_to_write] = write_series(file_to_sort, supporting_files[index_of_file_to_write]);
			else
				++amount_of_empty_series[index_of_file_to_write];
		}
	}

	for (int i = 0; i < amount_of_supporting_files - 1; ++i)
		supporting_files[i].close();

	file_to_sort.close();
	delete[] supporting_files;
	delete[] last_recorded_number;
	/*for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
		cout << "File " << i + 1 << ":\n";
		display(supporting_files_names[i]);
		cout << "------------------------" << endl;
	}*/
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

int FileSorter::write_series(fstream& from, ofstream& destination) {
	int current_number;
	do {
		from.read((char*)&current_number, sizeof(current_number));
		destination.write((char*)&current_number, sizeof(current_number));
	} while (from.peek() != EOF && get_next_number(from) >= current_number);

	return current_number; //last recorded number
}


void FileSorter::polyphase_merge_sort() {
	fstream* active_supporting_files = new fstream[amount_of_supporting_files];

	for (int i = 0; i < amount_of_supporting_files - 1; ++i) {
		active_supporting_files[i].open(supporting_files_names[i], ios::in | ios::binary);
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

		/*for (int i = 0; i < amount_of_supporting_files; ++i) {
			cout << supporting_files_names[i] << ": " << endl;
			display(supporting_files_names[i]);
			cout << "------------------------" << endl;
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
		int i = 0, index_of_file_with_min_element = 0, min = get_next_number(active_supporting_files[active_supporting_files_indexes[0]]);
		while (i < amount_of_active_files - 1) {
			++i;
			int current_element = get_next_number(active_supporting_files[active_supporting_files_indexes[i]]);
			if (current_element < min) {
				min = current_element;
				index_of_file_with_min_element = i;
			}
		}
		active_supporting_files[active_supporting_files_indexes[index_of_file_with_min_element]].read((char*)&min, sizeof(min));
		active_supporting_files[supporting_files_names_indexes[amount_of_supporting_files-1]].write((char*)&min, sizeof(min));

		if (get_next_number(active_supporting_files[active_supporting_files_indexes[index_of_file_with_min_element]]) < min) {
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
}