/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../Pool.hpp"

Pool::Pool() : size(0)
{
}

Pool::~Pool()
{
	this->Release();
}

void
Pool::RemoveAt(int&& index)
{
	this->size--;
	this->objects.erase(this->objects.begin() + index);
}

void
Pool::RemoveAt(const int& index)
{
	this->size--;
	this->objects.erase(this->objects.begin() + index);
}

void
Pool::Release(void)
{
	if (!this->deleted)
	{
		this->deleted = true;
		this->objects.clear();
	}
}

int
Pool::Size(void)
{
	return (this->size);
}

bool
Pool::IsEmpty(void)
{
	return (!static_cast<bool>(this->size));
}
