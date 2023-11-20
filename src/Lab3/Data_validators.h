#pragma once

#include "Data_converters.h"
#include <fstream>
bool is_number(const string& input);
int get_input(TextBox^ source);

bool is_empty_file(ifstream& file);