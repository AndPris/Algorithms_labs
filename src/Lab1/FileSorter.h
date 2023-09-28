#pragma once

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileSorter {
	const int amount_of_supporting_files;

	string file_to_sort_path;
	string* supporting_files_names;
	int	*active_supporting_files_indexes;
	int* ideal_amount_of_series, *amount_of_empty_series;
	size_t *start_position_of_reading;

	int level;
public:
	FileSorter(string file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files);

	void make_initial_spliting();
	void select_supporting_file_to_write_series(int& index_of_file_to_write);
	int write_series(ifstream& from, ofstream& destination);

	int get_next_number(ifstream& from);

	void polyphase_merge_sort();
	void merge_one_serie(int amount_of_active_files, ifstream* active_supporting_files, ofstream& output_file);

	~FileSorter();
};

