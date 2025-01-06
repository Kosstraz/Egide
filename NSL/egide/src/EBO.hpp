/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_EBO_HPP
#define EGIDE_EBO_HPP

# include "IsEmpty.hpp"

template <typename T, bool BIsEmpty = Types::IsEmpty<T>>
struct EBO
{
};

template <typename T>
struct EBO<T, false>
{
	EBO() = default;

	T	obj;
};

template <typename T>
struct EBO<T, true>
{
	EBO() = default;
};

#endif
