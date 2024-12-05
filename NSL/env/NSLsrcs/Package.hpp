/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_PACKAGE_HPP
#define NSL_PACKAGE_HPP

# include "Meta.hpp"
# include <exception>

// Package class encapsulates any many args
// Can be unpack with the Unpack/NSUnpack class
template <typename T, typename ... TArgs>
class Package
{
public:
	Package(const T& v, const TArgs&... rest) : value(v), rest(rest...)
	{}

	Package(T&& v, const TArgs&... rest) : value(Meta::Move(v)), rest(rest...)
	{}

	Package(const Package<T, TArgs...>& pack) : value(pack.v), rest(pack.rest)
	{}

	//Package(unsigned int&& i, const T& v, const TArgs&... rest) : index(Meta::Move(i)), value(v), rest(i + 1U, rest...)
	//{}

	//operator T() const
	//{
	//	return (this->value);
	//}

	Package<T, TArgs...>&	operator =(const Package<T, TArgs...>& pack)
	{
		//this->index = pack.index;
		this->value = pack.value;
		this->rest	= pack.rest;
	}

	/*auto&	test(Package<T, TArgs...> pack)
	{
		if (pack.index == index)
			return (pack.value);
		throw (std::exception());
	}

	auto&	operator [](const unsigned int& index)
	{
		if (this->index == index)
			return (this->value);
		Package<TArgs...>	tmp(this->rest);

		for (unsigned int i = 0U ; i < index && !tmp.last ; i++)
		{
			try
			{
				auto&	ret = test(tmp);
				return (ret);
			}
			catch (...)
			{
				tmp = tmp.rest;
			}
		}
		return (this->value); //! <-- throw an exception
	}*/

public:
	//unsigned int		index;
	T					value;
	Package<TArgs...>	rest;
	inline static constexpr bool	last = false;
};

template <>
class Package<void>
{
};


// Package class encapsulates any many args
// Can be unpack with the Unpack/NSUnpack class
template <typename T>
class Package<T>
{
public:
	Package(const T& v) : value(v)
	{}

	Package(const Package<T>& pack) : value(pack.value)
	{}

	//Package(unsigned int&& i, const T& v) : value(v), index(Meta::Move(i))
	//{}
	
	//Package(unsigned int&& i, T&& v) : value(Meta::Move(v)), index(Meta::Move(i))
	//{}// Faire pour que les types listes littéraux fonctionnent

	//operator T() const
	//{
	//	return (this->value);
	//}

	Package<T>&	operator =(const Package<T>& pack)
	{
		//this->index = pack.index;
		this->value = pack.value;
	}

	/*T&	operator [](int index)
	{
		if (this->index == index)
			return (value);
		return (T()); //! <-- throw an exception
	}*/

public:
	T					value;
	//unsigned int		index;
	inline static constexpr bool	last = true;

};

#endif
