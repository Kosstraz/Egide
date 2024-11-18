/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_SMARTPTR_HPP
#define NSL_SMARTPTR_HPP

# define MAX_SMARTPTR 65536

# include "IsSubclassOf.hpp"

// A smart pointer
template <typename T>
class SmartPtr final
{
	typedef unsigned short	maxsptr_t;

public:
	SmartPtr()							noexcept;
	SmartPtr(SmartPtr<T>&& sPtr)		noexcept;
	SmartPtr(const SmartPtr<T>& sPtr)	noexcept;
	SmartPtr(T* sPtr)					noexcept;
	SmartPtr(T&& sPtr)					noexcept;
	SmartPtr(const T& sPtr)				noexcept;

		//* Polymorphism edges cases *//
	template <typename U>
	requires Types::IsSubclassOf<T, U>
	SmartPtr(const SmartPtr<U>& sPtr)	noexcept;
	template <typename U>
	requires Types::IsSubclassOf<T, U>
	SmartPtr(U* sPtr)					noexcept;
	template <typename U>
	requires Types::IsSubclassOf<T, U>
	SmartPtr(U&& sPtr)					noexcept;
	template <typename U>
	requires Types::IsSubclassOf<T, U>
	SmartPtr(const U& sPtr)				noexcept;

	~SmartPtr() noexcept;

	void	destroy()					noexcept;
	void	destroyForce();
	[[nodiscard]]
	T*		ptr()						noexcept;
	[[nodiscard]]
	T*		get()						noexcept;
	T		val()				const	noexcept;
	maxsptr_t	HowMany()		const	noexcept;
	maxsptr_t*	CounterPtr()	const	noexcept;

private:
	void		matchWithNew(T* newPtr, maxsptr_t* newCount);

private:
	T*			_ptr  = nullptr;
	maxsptr_t*	count = nullptr;

public:
	SmartPtr<T>&	operator=(SmartPtr<T>&& other)		noexcept;
	SmartPtr<T>&	operator=(const SmartPtr<T>& other)	noexcept;
	T*				operator->()	const;
	const T&		operator*()		const;
};

# include "template/SmartPtr.inl"
#endif
