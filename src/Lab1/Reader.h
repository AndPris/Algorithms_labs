#pragma once

#include <iostream>
#include <Windows.h>
using namespace std;


class Reader
{
protected:
	DWORD data_size;
	DWORD recorded_data_size;
	int* data;
public:
	virtual int read() = 0;
	virtual void read_range(int*& dest_begin, int*& dest_end, int size_in_mb) = 0;

	bool is_end() const;

	virtual int peek() = 0;

	virtual void open_from_beggining() = 0;
};

