#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "RandomGenerator.h"
using namespace std;


class FileHandler {
	const int size_of_initial_file_in_mb;
	const int amount_of_suporting_files;

	string path_to_folder;
	string file_extension;
	string initial_file_name;
	string supporting_file_prefix;
	string *supporting_files_names;
public:
	FileHandler(int size_of_initial_file_in_mb, int amount_of_supporting_files);

	void create_initial_file();
	void display_initial_file();

	~FileHandler();
};

