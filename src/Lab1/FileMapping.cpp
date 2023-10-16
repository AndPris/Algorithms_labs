#include "FileMapping.h"

FileMapping::FileMapping(const wchar_t* file_path) : file_path(file_path) {
	_SYSTEM_INFO s;
	GetSystemInfo(&s);
	memory_allocation_granularity = s.dwAllocationGranularity;
	part_size_in_granularity = 10 * 1024 * 1024 / memory_allocation_granularity;

	open(GENERIC_READ | GENERIC_WRITE, OPEN_ALWAYS, PAGE_READWRITE, FILE_MAP_READ | FILE_MAP_WRITE, part_size_in_granularity);
}

void FileMapping::open(DWORD creation_access, DWORD creation_disposition, DWORD protect, DWORD view_access, int part_size_in_granularity) {
	file = CreateFile(file_path, creation_access, 0, NULL, creation_disposition, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		throw "File Creation error";
	}


	data_size = GetFileSize(file, NULL);
	part_size = part_size_in_granularity * memory_allocation_granularity;


	file_mapping = CreateFileMapping(file, NULL, protect, 0, 0, NULL);
	if (file_mapping == NULL) {
		CloseHandle(file);
		throw "File Mapping Creation error";
	}

	mapped_data = MapViewOfFile(file_mapping, view_access, 0, 0, (part_size > data_size) ? data_size : part_size);
	recorded_data_size = 0;
	part_counter = 1;
	this->view_access = view_access;

	if (mapped_data == NULL) {
		CloseHandle(file_mapping);
		CloseHandle(file);
		throw "Map View error";
	}

	data = static_cast<int*>(mapped_data);
	is_open = true;
}

void FileMapping::open_from_beggining() {
	UnmapViewOfFile(mapped_data);
	mapped_data = MapViewOfFile(file_mapping, view_access, 0, 0, (part_size > data_size) ? data_size : part_size);
	recorded_data_size = 0;
	part_counter = 1;
	this->view_access = view_access;

	if (mapped_data == NULL) {
		CloseHandle(file_mapping);
		CloseHandle(file);
		throw "Map View error";
	}

	data = static_cast<int*>(mapped_data);
}

int FileMapping::read() {
	int number = data[(recorded_data_size - part_size * (part_counter - 1)) / sizeof(int)];
	recorded_data_size += sizeof(int);

	if (recorded_data_size % part_size == 0)
		switch_part();

	return number;
}
void FileMapping::read_range(int*& dest_begin, int*& dest_end, int size_in_mb) {
	DWORD size_in_bytes = size_in_mb * 1024 * 1024;
	dest_begin = data + ((recorded_data_size - part_size * (part_counter - 1)) / sizeof(int));

	DWORD actual_size_of_data;
	if (recorded_data_size + size_in_bytes > data_size)
		actual_size_of_data = (data_size - recorded_data_size) / sizeof(int);
	else if (recorded_data_size + size_in_bytes > part_size * part_counter)
		actual_size_of_data = (part_size * part_counter - recorded_data_size) / sizeof(int);
	else
		actual_size_of_data = size_in_bytes / sizeof(int);

	dest_end = data + actual_size_of_data;
	recorded_data_size += actual_size_of_data * sizeof(int);

	if (recorded_data_size % part_size == 0)
		switch_part();
}
int FileMapping::peek() {
	if (is_end())
		return 0;

	return data[(recorded_data_size - part_size * (part_counter - 1)) / sizeof(int)];
}

void FileMapping::switch_part() {
	if (is_end())
		return;

	LPVOID mapped_data = MapViewOfFile(file_mapping, view_access, 0, part_counter * part_size, (part_size > data_size - part_size * part_counter ? data_size - part_size * part_counter : part_size));
	if (mapped_data == NULL) {
		CloseHandle(file_mapping);
		CloseHandle(file);
		throw "Map View error";
	}

	data = static_cast<int*>(mapped_data);
	part_counter++;
}


void FileMapping::close() {
	if (!is_open)
		return;

	CloseHandle(file);
	CloseHandle(file_mapping);
	UnmapViewOfFile(mapped_data);
	is_open = false;
}

FileMapping::~FileMapping() {
	close();
}