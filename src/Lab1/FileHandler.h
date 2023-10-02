#pragma once

#include <string>
#include <fstream>
using namespace std;


class FileHandler {
	const int size_of_initial_file_in_mb;

	const wchar_t* initial_file_path;
public:
	FileHandler(const wchar_t* initial_file_path, int size_of_initial_file_in_mb);

	void create_initial_file() const;

	const wchar_t* get_initial_file_path() const;
};

