#include "ArrayReader.h"

ArrayReader::ArrayReader(int* array) {
	data = array;
	recorded_data_size = 0;
	data_size = sizeof(data);
}

int ArrayReader::read() {
	int number = data[recorded_data_size / sizeof(int)];
	recorded_data_size += sizeof(int);

	return number;
}
void ArrayReader::read_range(int*& dest_begin, int*& dest_end, int size_in_mb) {
	DWORD size_in_bytes = size_in_mb * 1024 * 1024;
	dest_begin = data + (recorded_data_size / sizeof(int));

	DWORD actual_size_of_data;
	if (recorded_data_size + size_in_bytes > data_size)
		actual_size_of_data = (data_size - recorded_data_size) / sizeof(int);
	else
		actual_size_of_data = size_in_bytes / sizeof(int);

	dest_end = data + actual_size_of_data;
	recorded_data_size += actual_size_of_data * sizeof(int);
}


int ArrayReader::peek() {
	if (is_end())
		return 0;

	return data[recorded_data_size/ sizeof(int)];
}

void ArrayReader::open_from_beggining() {
	recorded_data_size = 0;
}

ArrayReader::~ArrayReader() {
	delete[] data;
}