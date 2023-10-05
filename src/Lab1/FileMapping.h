#pragma once

#include <algorithm>
#include "Reader.h"
using namespace std;

class FileMapping : public Reader {
	const wchar_t* file_path;

	DWORD memory_allocation_granularity;
	int part_size_in_granularity;

	HANDLE file;
	DWORD part_size;
	HANDLE file_mapping;
	LPVOID mapped_data;

	DWORD view_access;

	bool is_open;

	int part_counter;

private:
	void open(DWORD creation_access, DWORD creation_disposition, DWORD protect, DWORD view_access, int part_size_in_granularity);

	void switch_part();
public:
	FileMapping(const wchar_t* file_path);

	int read() override;
	void read_range(int*& dest_begin, int*& dest_end, int size_in_mb) override;
	int peek() override;

	void open_from_beggining() override;
	void close();

	~FileMapping();
};

