/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_BASELIST_HPP
#define NSL_BASELIST_HPP

# include "Iterator.hpp"

template <typename T>
class BaseList
{
public:
	FORCEINLINE
	BaseList()							noexcept;
	FORCEINLINE
	BaseList(const BaseList& al)	noexcept;
	FORCEINLINE
	BaseList(BaseList&& al)			noexcept;
	FORCEINLINE
	virtual ~BaseList()					noexcept;

	FORCEINLINE
	uint64	Size()	const noexcept;

	FORCEINLINE
	Iterator<T>&			begin()				noexcept;
	FORCEINLINE
	Iterator<T>&			end()				noexcept;
	FORCEINLINE
	Iterator<const T>		cbegin()	const	noexcept;
	FORCEINLINE
	Iterator<const T>		cend()		const	noexcept;

protected:
	T*			data;
	uint64		size;
	Iterator<T>	first;
	Iterator<T>	last;
};

# include "template/BaseList.inl"
#endif
