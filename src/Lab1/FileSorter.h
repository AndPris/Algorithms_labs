#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <algorithm>
using namespace std;

class FileSorter {
	const int amount_of_supporting_files;

	const wchar_t* file_to_sort_path;
	string* supporting_files_names;
	int	*active_supporting_files_indexes, *supporting_files_names_indexes,
		*ideal_amount_of_series, *amount_of_empty_series, *first_numbers;

	int level;
	DWORD memory_allocation_granularity;
public:
	FileSorter(const wchar_t* file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files);

	void pre_sort();

	void make_initial_spliting();
	void select_supporting_file_to_write_series(int& index_of_file_to_write);
	int write_series(int* from, ofstream& destination, int& part_counter, DWORD& file_size, DWORD part_size, DWORD& recorded_data_size, HANDLE& file_mapping, LPVOID& mapped_data);

	int get_next_number(fstream& from);

	void polyphase_merge_sort();
	void merge_one_serie(int amount_of_active_files, fstream* active_supporting_files);

	~FileSorter();
};

