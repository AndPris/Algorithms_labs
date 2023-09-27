#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "RandomGenerator.h"
using namespace std;


class FileHandler {
	const int size_of_initial_file_in_mb;

	string initial_file_path;
public:
	FileHandler(string initial_file_path, int size_of_initial_file_in_mb);

	void create_initial_file() const;
	void display_initial_file() const;

	string get_initial_file_path() const;
};

