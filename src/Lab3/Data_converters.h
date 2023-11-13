#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace std;
using namespace System;

string String_to_string(String^ data);
const char* String_to_char_string(String^ data);
String^ char_string_into_String(const char* data);