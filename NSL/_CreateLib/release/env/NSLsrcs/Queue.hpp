/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_QUEUE_HPP
#define NSL_QUEUE_HPP

# include "Iterator.hpp"
# include "BaseList.hpp"
# include "Meta.hpp"

template <typename T>
class Queue final : public BaseList<T>
{
public:
	Queue()				noexcept;
	Queue(const Queue&)	noexcept;
	Queue(Queue&&)		noexcept;
	~Queue()			noexcept;

	void	Push(const T& elem)	noexcept;
	void	Push(T&& elem)		noexcept;
	void	PushRef(T& elem_ref)	noexcept;

	T&&		Pop()	noexcept;

	/*void	Insert(const T& elem,	const int& at)	noexcept;
	void	Insert(T&& elem,		const int& at)	noexcept;
	void	InsertRef(T& elem_ref,	const int& at)	noexcept;

	void	Insert(const T& elem,	int&& at)	noexcept;
	void	Insert(T&& elem,		int&& at)	noexcept;
	void	InsertRef(T& elem_ref,	int&& at)	noexcept;*/	//! For List class

private:

public:
	//FORCEINLINE
	//Iterator<T>		operator +(const uint64&)	noexcept;
	//FORCEINLINE
	//Iterator<T>		operator +(uint64&&)		noexcept;
	//FORCEINLINE
	//T&	operator <<(T&)			noexcept;

	//FORCEINLINE
	//Iterator<T>&	operator +=(const T&)	noexcept;
	//FORCEINLINE
	//Iterator<T>&	operator +=(T&&)		noexcept;
	//FORCEINLINE
	//T&	operator <<=(T&)		noexcept;

	FORCEINLINE
	T&			operator [](int&& index)		noexcept;
	FORCEINLINE
	T&			operator [](const int& index)	noexcept;
	FORCEINLINE
	Queue<T>&	operator =(const Queue&)		noexcept;
	FORCEINLINE
	Queue<T>&	operator =(Queue&&)				noexcept;
};

# include "template/Queue.inl"
#endif
