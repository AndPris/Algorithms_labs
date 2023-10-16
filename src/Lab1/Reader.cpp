#include "Reader.h"

bool Reader::is_end() const {
	return recorded_data_size >= data_size;
}