#include "Data_converters.h"


string String_to_string(String^ data) {
	return msclr::interop::marshal_as<string>(data);
}
String^ string_to_String(string data) {
	return msclr::interop::marshal_as<String^>(data);
}

const char* String_to_char_string(String^ data) {
	string str_data = String_to_string(data);
	return str_data.c_str();

}
String^ char_string_into_String(const char* data) {
	return msclr::interop::marshal_as<String^>(data);
}
