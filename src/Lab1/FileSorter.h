#pragma once

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileSorter {
	const int amount_of_supporting_files;

	string file_to_sort_path;
	string *supporting_files_names;
	int* ideal_amount_of_series, *amount_of_empty_series;

	int level;
public:
	FileSorter(string file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files);

	void make_initial_spliting();
	void select_supporting_file_to_write_series(int& index_of_file_to_write);
	int write_series(ifstream& from, ofstream& destination);

	~FileSorter();
};

