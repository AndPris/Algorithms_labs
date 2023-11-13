#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace std;
using namespace System;
using namespace Windows::Forms;

string String_to_string(String^ data);
const char* String_to_char_string(String^ data);
String^ char_string_into_String(const char* data);