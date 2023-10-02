#pragma once

#include <Windows.h>
#include <algorithm>
using namespace std;

class FileMapping {
	const wchar_t* file_path;

	DWORD memory_allocation_granularity;

	HANDLE file;
	DWORD file_size;
	DWORD part_size;
	HANDLE file_mapping;
	LPVOID mapped_data;

	DWORD view_access;

	int part_counter;
	DWORD recorded_data_size;

	int* data;

public:
	FileMapping(const wchar_t* file_path);

	void open(DWORD creation_access, DWORD creation_disposition, DWORD protect, DWORD view_access, int part_size_in_granularity);

	void partial_sort();

	bool is_end();

	int read();
	void switch_part();

	int peek();

	void close();
};

