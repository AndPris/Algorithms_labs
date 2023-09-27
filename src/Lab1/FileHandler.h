#pragma once

#include <string>
#include <random>
using namespace std;


class FileHandler
{
	const int amount_of_suporting_files;
	
	string file_extension;
	string initial_file_name;
	string supporting_file_prefix;
	string *supporting_files_names;

	int generate_number_from_range(int low_border, int top_border);
public:
	FileHandler(int amount_of_supporting_files);

	~FileHandler();
};

