/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_SMARTPTR_INL
#define EGIDE_SMARTPTR_INL

# include <iostream>
# include "../SmartPtr.hpp"

/*//////////*/
/*  PUBLIC  */
/*//////////*/

template <typename T>
SmartPtr<T>::SmartPtr() noexcept
{
	this->matchWithNew(nullptr, nullptr);
}

template <typename T>
SmartPtr<T>::SmartPtr(SmartPtr<T>&& sPtr) noexcept
{
	if (this != &sPtr && this->_ptr != sPtr._ptr)
	{
		this->matchWithNew(sPtr._ptr, sPtr.count);
		sPtr._ptr = nullptr;
		sPtr.count = nullptr;
	}
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& sPtr) noexcept
{
	if (this != &sPtr && this->_ptr != sPtr._ptr)
	{
		this->matchWithNew(sPtr._ptr, sPtr.count);
		if (this->_ptr != nullptr)
		{
			(*sPtr.count)++;
			this->count = sPtr.count;
		}
	}
}

template <typename T>
SmartPtr<T>::SmartPtr(T* rvalue__ptrnew) noexcept
{
	this->matchWithNew(rvalue__ptrnew, new maxsptr_t(1));
}

template <typename T>
SmartPtr<T>::SmartPtr(T&& rvalue__ptrnew) noexcept
{
	this->matchWithNew(new T(rvalue__ptrnew), new maxsptr_t(1));
}

template <typename T>
SmartPtr<T>::SmartPtr(const T& _ptrnew) noexcept
{
	this->matchWithNew(new T(_ptrnew), new maxsptr_t(1));
}

template <typename T>
SmartPtr<T>::~SmartPtr() noexcept
{
	this->destroy();
}

template <typename T>
void
SmartPtr<T>::DeleteOccurrence() noexcept
{
	this->_ptr = nullptr;
	(*this->count)--;
	this->count = nullptr;
}

template <typename T>
void
SmartPtr<T>::destroy() noexcept
{
	if (this->count != nullptr && *this->count > 0)
	{
		if ((*this->count)-- == 1)
		{
			delete this->_ptr;
			delete this->count;
		}
		this->_ptr = nullptr;
		this->count = nullptr;
	}
	//else
	//	std::cerr << "SmartPtr<int> impossible/nothing to destroyed" << std::endl;
}

template <typename T>
void
SmartPtr<T>::destroyForce()
{
	delete this->_ptr;
	delete this->count;
	this->_ptr = nullptr;
	this->count = nullptr;
	//std::cout << "Force destroy" << std::endl;
}

template <typename T>
T*
SmartPtr<T>::ptr() noexcept
{
	return (this->_ptr);
}

template <typename T>
const T*
SmartPtr<T>::const_get() const noexcept
{
	return (const_cast<const T*>(this->_ptr));
}

template <typename T>
T*
SmartPtr<T>::get() noexcept
{
	return (this->_ptr);
}

template <typename T>
T
SmartPtr<T>::val() const noexcept
{
	return (*(this->_ptr));
}

template <typename T>
unsigned short
SmartPtr<T>::HowMany()	const noexcept
{
	return (*(this->count));
}

template <typename T>
unsigned short*
SmartPtr<T>::CounterPtr()	const noexcept
{
	return (this->count);
}

/*///////////*/
/*  PRIVATE  */
/*///////////*/

template <typename T>
void
SmartPtr<T>::matchWithNew(T* newPtr, maxsptr_t* newCount)
{
	if (this->_ptr != newPtr)
	{
		if (this->count != nullptr && *this->count == 1)
		{
			delete this->count;
			delete this->_ptr;
		}
		this->count = newCount;
		this->_ptr = newPtr;
	}
}

/*////////////*/
/*  OPERATOR  */
/*////////////*/

template <typename T>
SmartPtr<T>&
SmartPtr<T>::operator=(SmartPtr<T>&& other) noexcept
{
	if (this != &other && this->_ptr != other.ptr())
	{
		matchWithNew(other._ptr, other.count);
		other._ptr = nullptr;
		other.count = nullptr;
	}
	return (*this);
}

template <typename T>
SmartPtr<T>&
SmartPtr<T>::operator=(const SmartPtr<T>& other) noexcept
{
	if (this != &other && this->_ptr != other.ptr())
	{
		matchWithNew(other._ptr, other.count);
		if (other._ptr)
			(*this->count)++;
	}
	return (*this);
}

template <typename T>
T*
SmartPtr<T>::operator->() const
{
	return (this->_ptr);
}

template <typename T>
const T&
SmartPtr<T>::operator*() const
{
	return (*(this->_ptr));
}

/*////////////////*/
/*  POLYMORPHISM  */
/*////////////////*/

template <typename T>
template <typename U>
requires Types::IsSubclassOf<T, U>
SmartPtr<T>::SmartPtr(const SmartPtr<U>& sPtr) noexcept
{
	if (this->_ptr != sPtr.ptr())
	{
		this->matchWithNew(sPtr.ptr(), sPtr.CounterPtr());
		if (this->_ptr != nullptr)
		{
			(*sPtr.CounterPtr())++;
			this->count = sPtr.CounterPtr();
		}
	}
}

template <typename T>
template <typename U>
requires Types::IsSubclassOf<T, U>
SmartPtr<T>::SmartPtr(SmartPtr<U>&& sPtr) noexcept
{
	if (this->_ptr != sPtr.ptr())
	{
		this->matchWithNew(sPtr.ptr(), sPtr.CounterPtr());
		if (this->_ptr != nullptr)
		{
			(*sPtr.CounterPtr())++;
			this->count = sPtr.CounterPtr();
		}
		sPtr.DeleteOccurrence();
	}
}

template <typename T>
template <typename U>
requires Types::IsSubclassOf<T, U>
SmartPtr<T>::SmartPtr(U* rvalue__ptrnew) noexcept
{
	this->matchWithNew(rvalue__ptrnew, new maxsptr_t(1));
}

template <typename T>
template <typename U>
requires Types::IsSubclassOf<T, U>
SmartPtr<T>::SmartPtr(U&& rvalue__ptrnew) noexcept
{ 
	this->matchWithNew(new U(rvalue__ptrnew), new maxsptr_t(1));
}

template <typename T>
template <typename U>
requires Types::IsSubclassOf<T, U>
SmartPtr<T>::SmartPtr(const U& _ptrnew) noexcept
{
	this->matchWithNew(new U(_ptrnew), new maxsptr_t(1));
}

#endif
