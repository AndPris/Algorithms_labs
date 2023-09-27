#pragma once

#include <string>
using namespace std;

class FileSorter
{
	const int amount_of_suporting_files;

	string file_to_sort_path;
	string* supporting_files_names;
public:
	FileSorter(string file_to_sort_path, string file_extension, string supporting_file_prefix, int amount_of_supporting_files);

	~FileSorter();
};

