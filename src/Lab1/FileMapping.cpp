#include "FileMapping.h"

FileMapping::FileMapping(const wchar_t* file_path) : file_path(file_path) {
	_SYSTEM_INFO s;
	GetSystemInfo(&s);
	memory_allocation_granularity = s.dwAllocationGranularity;
}

void FileMapping::open(DWORD creation_access, DWORD creation_disposition, DWORD protect, DWORD view_access, int part_size_in_granularity) {
	file = CreateFile(file_path, creation_access, 0, NULL, creation_disposition, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		throw "File Creation error";
	}


	file_size = GetFileSize(file, NULL);
	part_size = part_size_in_granularity * memory_allocation_granularity;


	file_mapping = CreateFileMapping(file, NULL, protect, 0, 0, NULL);
	if (file_mapping == NULL) {
		CloseHandle(file);
		throw "File Mapping Creation error";
	}

	mapped_data = MapViewOfFile(file_mapping, view_access, 0, 0, (part_size > file_size) ? file_size : part_size);
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

void FileMapping::partial_sort() {
	int amount_of_parts = (file_size % part_size) == 0 ? file_size / part_size : file_size / part_size + 1;

	part_size = (file_size / memory_allocation_granularity / amount_of_parts) * memory_allocation_granularity;

	for (int i = 0; i < amount_of_parts; i++) {
		DWORD offset = i * part_size;
		DWORD part_file_size = (i == amount_of_parts - 1) ? (file_size - offset) : part_size;

		LPVOID mapped_data = MapViewOfFile(file_mapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, offset, part_file_size);
		if (mapped_data == NULL) {
			CloseHandle(file_mapping);
			CloseHandle(file);
			throw "Map View error";
		}

		int* data = static_cast<int*>(mapped_data);
		sort(data, data + part_file_size / sizeof(int));
		UnmapViewOfFile(mapped_data);
	}
}

bool FileMapping::is_end() {
	return recorded_data_size >= file_size;
}

int FileMapping::read() {
	int i = (recorded_data_size - part_size * (part_counter - 1)) / sizeof(int);
	recorded_data_size += sizeof(int);

	int number = data[i];
	if (recorded_data_size % part_size == 0)
		switch_part();

	return number;
}

int FileMapping::peek() {
	if (is_end())
		return 0;

	int index = (recorded_data_size - part_size * (part_counter - 1)) / sizeof(int);

	return data[index];
}

void FileMapping::switch_part() {
	if (is_end())
		return;

	LPVOID mapped_data = MapViewOfFile(file_mapping, view_access, 0, part_counter * part_size, (part_size > file_size - part_size * part_counter ? file_size - part_size * part_counter : part_size));
	if (mapped_data == NULL) {
		CloseHandle(file_mapping);
		CloseHandle(file);
		throw "Map View error";
	}

	data = static_cast<int*>(mapped_data);
	part_counter++;
}

void FileMapping::close() {
	CloseHandle(file);
	CloseHandle(file_mapping);
	UnmapViewOfFile(mapped_data);
}