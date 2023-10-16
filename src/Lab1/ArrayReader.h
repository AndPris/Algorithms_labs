#pragma once

#include "Reader.h"

class ArrayReader : public Reader {
public:
	ArrayReader(int* array);

	int read() override;
	void read_range(int*& dest_begin, int*& dest_end, int size_in_mb) override;

	void open_from_beggining() override;


	int peek() override;

	~ArrayReader();
};

