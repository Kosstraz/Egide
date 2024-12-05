/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../String.hpp"

String::String() : data(new char[STRING_PREALLOC_SIZE + 1ULL]), size(0ULL), capacity(STRING_PREALLOC_SIZE), allocated(true)
{
}

//String::String(const std::string& str) : data(String::CString(str.data())), size(0ULL), allocated(true), size_calculated(false)
//{
//}

String::String(const String& str) : data(String::CString(str)), size(str.size), capacity(STRING_PREALLOC_SIZE), allocated(true)
{
}//Todo: faire le préallouage

String::String(const char* data) : size(String::Size(data)), capacity(STRING_PREALLOC_SIZE), allocated(true)
{
	if (this->size > this->capacity)
		this->capacity = this->size * 2ULL;
	this->data = Allocator<char>::Reserve(this->capacity + 1ULL, 32);
	//this->data = new char[this->capacity + 1ULL];
	String::__ncopy__(this->data, data, this->size);
	this->data[this->size] = '\0';
}

String::~String()
{
	this->Destroy();
}

