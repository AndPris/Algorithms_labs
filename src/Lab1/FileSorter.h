#pragma once

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileSorter {
	const int amount_of_supporting_files;

	string file_to_sort_path;
	string* supporting_files_names;
	int	*active_supporting_files_indexes, *supporting_files_names_indexes,
		*ideal_amount_of_series, *amount_of_empty_series;

	int level;
public:
	FileSorter(string file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files);

	void make_initial_spliting();
	void select_supporting_file_to_write_series(int& index_of_file_to_write);
	int write_series(fstream& from, ofstream& destination);

	int get_next_number(fstream& from);

	void polyphase_merge_sort();
	void merge_one_serie(int amount_of_active_files, fstream* active_supporting_files);

	~FileSorter();
};

