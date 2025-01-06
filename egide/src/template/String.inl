/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_STRING_INL
#define EGIDE_STRING_INL

# include "../String.hpp"
# include <cstring>

bool
String::Contains(const char* data) const
{
	return (strstr(this->data, data) ? true : false);
}

bool
String::Contains(const String& str) const
{
	return (strstr(this->data, str.data) ? true : false);
}

#pragma region CompareWith
int
String::CompareWith(const char* data) const
{
	return (strcmp(this->data, data));
}

int
String::CompareWith(const String& str) const
{
	return (strcmp(this->data, str.data));
}

int
String::CompareNByteWith(const char* data, unsigned int n) const
{
	return (strncmp(this->data, data, n));
}

int
String::CompareNByteWith(const String& str, unsigned int n) const
{
	return (strncmp(this->data, str.data, n));
}
#pragma endregion






#pragma region IsEqual
bool
String::IsEqualWith(const char* data) const
{
	return (!strcmp(this->data, data));
}

bool
String::IsEqualWith(const String& str) const
{
	return (!strcmp(this->data, str.data));
}

bool
String::IsNByteEqualWith(const char* data, unsigned int n) const
{
	return (!strncmp(this->data, data, n));
}

bool
String::IsNByteEqualWith(const String& str, unsigned int n) const
{
	return (!strncmp(this->data, str.data, n));
}
#pragma endregion



#pragma region Reserve
void
String::Reserve(const uint64& nbyte)	noexcept
{
	char* const	ref = this->data;
	this->data = Allocator<char>::Reserve(nbyte);//new char[nbyte];
	if (this->size > 0ULL)
		String::__ncopy__(this->data, ref, this->size);
	delete[](ref);
}
#pragma endregion




#pragma region Replace
void
String::Replace(const char* data) noexcept
{
	this->__replace__(data);
}

void
String::Replace(const String& str) noexcept
{
	this->__replace__(str.data);
}

void
String::Overwrite(const char* data) noexcept
{
	this->__replace__(data);
}

void
String::Overwrite(const String& str) noexcept
{
	this->__replace__(str.data);
}
#pragma endregion






#pragma region Strjoin
void
String::Join(const char* data) noexcept
{
	this->__join__(data);
}

void
String::Join(const String& str) noexcept
{
	this->__join__(str);
}

void
String::Append(const char* data) noexcept
{
	this->__join__(data);
}

void
String::Append(const String& str) noexcept
{
	this->__join__(str);
}

#include <iostream>
void
String::__join__(const String& str) noexcept
{
	const uint64	thisLen = this->size;
	const uint64	dataLen = str.size;
	const uint64	totaLen = thisLen + dataLen;
	char* const		ref = this->data;

	this->_setSize_(totaLen);
	if (totaLen > this->capacity)
	{
		this->capacity = totaLen * 2ULL;
		this->data = Allocator<char>::Reserve(this->capacity + 1ULL, 32UL);
		//this->data = new char[this->capacity + 1ULL];
	}
	else
		this->allocated = false;
	if (this->allocated)
	{
		String::__ncopy__(this->data, ref, thisLen);
		if (this->allocated)
			Allocator<char>::Free(ref);
	}
	String::__ncopy__(&this->data[thisLen], str.data, dataLen);
	this->data[totaLen] = '\0';
	this->allocated = true;
}
#pragma endregion






#pragma region Strlen
uint64
String::Len() const noexcept
{
	return (this->size);
}

uint64
String::Size() const noexcept
{
	return (this->size);
}

uint64
String::Len(const String& str) noexcept
{
	return (str.size);
}

uint64
String::Size(String& str) noexcept
{
	return (str.size);
}

uint64
String::Size(const char* cstr) noexcept
{
	return (String::__length__(cstr));

}
#pragma endregion





void
String::Swap(String& str) noexcept
{
	Meta::Swap(*this, str);
}

void
String::Shuffle() noexcept
{
	this->data = strfry(this->data);
}

char*
String::CString(const String& str) noexcept
{
	const uint64	size	= str.size;
	char*			ret		= Allocator<char>::Reserve(size + 1ULL);//new char[size + 1ULL];
	String::__ncopy__(ret, str.data, size);
	ret[size] = '\0';
	return (ret);
}

char*
String::CString() noexcept
{
	const uint64	size	= this->size;
	char*			ret		= Allocator<char>::Reserve(size + 1ULL);//new char[size + 1ULL];
	String::__ncopy__(ret, this->data, size);
	ret[size] = '\0';
	return (ret);
}

void
String::Erase(const int& index) noexcept
{
	const uint64	totalSize = this->size - 1ULL;
	const uint64	secondPart= index + 1ULL;
	char* const		ref = this->data;

	if (static_cast<uint64>(index) >= totalSize) [[unlikely]]
		return ;
	String::__ncopy__(&this->data[index], &ref[secondPart], totalSize - index);
	this->data[totalSize] = '\0';
	this->allocated = true;
	this->_setSize_(totalSize);
}

bool
String::Empty() const
{
	return (!this->data || !this->data[0]);
}

constexpr const char*
String::Data() const noexcept
{
	return (this->data);
}

constexpr const char&
String::At(int index) const noexcept
{
	return (this->data[index]);
}

const char&	String::First() const noexcept
{
	return (*this->data);
}

const char&
String::Last() const noexcept
{
	return (this->data[this->size - 1]);
}

void
String::Clear() noexcept
{
	if (this->allocated && this->data)
		Allocator<char>::Free(this->data);//delete[](this->data);
	this->allocated = false;
	this->data = nullptr;
	this->_setSize_(0ULL);
}

void
String::Destroy() noexcept
{
	if (this->allocated && this->data)
		Allocator<char>::Free(this->data);
		//delete[](this->data);
	this->allocated = false;
	this->data = nullptr;
	this->_setSize_(0ULL);
}

void
String::_setSize_(uint64 newSize) noexcept
{
	this->size = newSize;
}





void
String::__replace__(const String& str) noexcept
{
	this->_setSize_(str.size);
	if (str.size > this->capacity)
	{
		if (this->allocated)
			Allocator<char>::Free(this->data);//delete[](this->data);
		this->capacity = str.size * 2ULL;
		this->data = Allocator<char>::Reserve(this->capacity + 1ULL);//new char[this->capacity + 1ULL];
	}
	//else if (this->capacity > STRING_capacity && str.size ) //Todo: faire un système d'auto-organisation de la mémoire
	String::__ncopy__(this->data, str.data, this->size);
	this->data[this->size] = '\0';
}






#pragma region __ncopy__
#if defined(AVX2)
void
String::__ncopy__(char* dest, const char* src, const uint64 nbyte) noexcept
{
	uint64			i			= 0ULL;
	const ulong		byteTotal	= static_cast<uint64>(nbyte / 32ULL);
	uint64			byteOffset	= nbyte - byteTotal * 32ULL; // modulo
	int256* const	c256		= (int256*)dest;
	int256* const	mem			= (int256*)src;
	int256			src256;

	for ( ; i < byteTotal ; i += 1UL)
	{
		src256 = _mm256_loadu_si256(&mem[i]);
		_mm256_storeu_si256(&c256[i], src256);
	}
	i *= 32UL;
	for ( ; byteOffset ; byteOffset--)
	{
		dest[i] = src[i];
		i++;
	}
}
#else
void
String::__ncopy__(char* dest, const char* src, const uint64 nbyte) noexcept
{
	for (uint64 i = 0 ; i < nbyte ; i++)
		dest[i] = src[i];
}
#endif
#pragma endregion




#pragma region __length__
#if defined(AVX2)
uint64
String::__length__() const noexcept
{
	uint64			i	= 0ULL;
	const int256	z	= _mm256_setzero_si256();
	const int256*	mem	= (const int256*)this->data;

	for ( ; ; i += 1ULL)
	{
		const int256	chunk	= _mm256_loadu_si256(&mem[i]);
		const int		result	= _mm256_movemask_epi8(_mm256_cmpeq_epi8(z, chunk));
		if (result)
			return (i * 32ULL + __builtin_ctz(result));

	}
	assert(false);
}
#elif defined(SSE2)
uint64
String::__length__() const noexcept
{
	uint64			i	= 0ULL;
	const int128	z	= _mm_setzero_si128();
	const int128*	mem	= (const int128*)this->data;

	for ( ; ; i += 1ULL)
	{
		const int128	chunk	= _mm_loadu_si128(&mem[i]);
		const int		result	= _mm_movemask_epi8(_mm_cmpeq_epi8(z, chunk));
		if (result)
			return (i * 16ULL + __builtin_ctz(result));
	}
	assert(false);
}
#else
uint64
String::__length__() const noexcept
{
	uint64 i = 0;
	for ( ; this->data[i] ; i++) ;
	return (i);
}
#endif
#pragma endregion







#pragma region static __length__
#if defined(AVX2)
uint64
String::__length__(const String& str) noexcept
{
	uint64				i	= 0ULL;
	const int256		z	= _mm256_setzero_si256();
	const int256* const	mem	= (const int256*)str.data;

	for ( ; ; i += 1ULL)
	{
		const int256	chunk	= _mm256_loadu_si256(&mem[i]);
		const int		result	= _mm256_movemask_epi8(_mm256_cmpeq_epi8(z, chunk));
		if (result)
			return (i * 32ULL + __builtin_ctz(result));

	}
	assert(false);
}
#elif defined(SSE2)
uint64
String::__length__(const String& str) noexcept
{
	uint64				i	= 0ULL;
	const int128		z	= _mm_setzero_si128();
	const int128* const	mem	= (const int128*)str.data;

	for ( ; ; i += 1ULL)
	{
		const int128	chunk	= _mm_loadu_si128(&mem[i]);
		const int		result	= _mm_movemask_epi8(_mm_cmpeq_epi8(z, chunk));
		if (result)
			return (i * 16ULL + __builtin_ctz(result));
	}
	assert(false);
}
#else
uint64
String::__length__(const String& str) noexcept
{
	uint64 i = 0;
	for ( ; str.data[i] ; i++) ;
	return (i);
}
#endif
#pragma endregion





#pragma region cstr* __length__
#if defined(AVX2)
uint64
String::__length__(const char* cstr) noexcept
{
	uint64				i	= 0ULL;
	const int256		z	= _mm256_setzero_si256();
	const int256* const	mem	= (const int256*)cstr;

	for ( ; ; i += 1ULL)
	{
		const int256	chunk	= _mm256_loadu_si256(&mem[i]);
		const int		result	= _mm256_movemask_epi8(_mm256_cmpeq_epi8(z, chunk));
		if (result)
			return (i * 32ULL + __builtin_ctz(result));

	}
	assert(false);
}
#elif defined(SSE2)
uint64
String::__length__(const char* cstr) noexcept
{
	uint64				i	= 0ULL;
	const int128		z	= _mm_setzero_si128();
	const int128* const	mem	= (const int128*)cstr;

	for ( ; ; i += 1ULL)
	{
		const int128	chunk	= _mm_loadu_si128(&mem[i]);
		const int		result	= _mm_movemask_epi8(_mm_cmpeq_epi8(z, chunk));
		if (result)
			return (i * 16ULL + __builtin_ctz(result));
	}
	assert(false);
}
#else
uint64
String::__length__(const char* cstr) noexcept
{
	uint64 i = 0ULL;
	for ( ; cstr[i] ; i++) ;
	return (i);
}
#endif
#pragma endregion




#endif
