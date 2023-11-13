#include "Data_validators.h"

bool is_number(const string& input) {
	for (char ch : input) {
		if (!isdigit(ch))
			return false;
	}
	return true;
}

int get_input(TextBox^ source) {
	string data = String_to_string(source->Text);

	if (data == "")
		throw "You must enter a key";

	if (!is_number(data))
		throw "You must enter a positive integer number";

	if (data.length() > 1 && data[0] == '0')
		throw "Number can't start with 0";

	return stoi(data);
}