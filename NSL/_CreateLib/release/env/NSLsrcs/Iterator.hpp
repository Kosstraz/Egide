/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_ITERATOR_HPP
#define NSL_ITERATOR_HPP

# include "Meta.hpp"

template <typename T>
class Iterator
{
public:
	Iterator()	= default;
	Iterator(T* addr);
	Iterator(const Iterator<T>&);
	Iterator(Iterator<T>&&);
	~Iterator()	= default;

	T*	get() noexcept;

protected:
	T*	obj = nullptr;

public:

	/*
		ASSIGNMENT
	*/

	FORCEINLINE
	Iterator<T>&	operator =(const Iterator<T>& it);

	FORCEINLINE
	Iterator<T>&	operator =(Iterator<T>&& it);

	FORCEINLINE
	Iterator<T>&	operator -=(const uint64& v);

	FORCEINLINE
	Iterator<T>&	operator +=(const uint64& v);

	FORCEINLINE
	Iterator<T>&	operator -=(uint64&& v);

	FORCEINLINE
	Iterator<T>&	operator +=(uint64&& v);

	/*
		ARITHMETIC
	*/

	FORCEINLINE
	Iterator<T>	operator -(uint64 v);

	FORCEINLINE
	Iterator<T>	operator +(uint64 v);

	/*
		MEMBER ACCESS
	*/

	FORCEINLINE
	Iterator<T>	operator [](const int& index);

	FORCEINLINE
	Iterator<T>	operator [](int&& index);

	FORCEINLINE
	T&	operator *();

	FORCEINLINE
	T*	operator ->();

	/*
		INCREMENT
		DECREMENT
	*/

	FORCEINLINE
	Iterator<T>&	operator ++();

	FORCEINLINE
	Iterator<T>		operator ++(int);
};

# include "template/Iterator.inl"
#endif
