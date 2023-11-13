#include "validation_functions.h"

void validate_file_path(std::string& path, std::string extension) {
	std::string file_extension = path.substr(path.length() - extension.length(), extension.length());
	if (file_extension != extension)
		path += extension;
}