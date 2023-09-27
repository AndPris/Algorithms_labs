#pragma once

#include <string>
#include <random>
using namespace std;


class FileHandler
{
	const int size_of_initial_file_in_mb;
	const int amount_of_suporting_files;

	string file_extension;
	string initial_file_name;
	string supporting_file_prefix;
	string *supporting_files_names;
public:
	FileHandler(int size_of_initial_file_in_mb, int amount_of_supporting_files);

	int generate_number_from_range(int low_border, int top_border);

	~FileHandler();
};

