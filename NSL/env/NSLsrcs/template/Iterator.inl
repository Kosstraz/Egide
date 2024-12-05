#include "../Iterator.hpp"

template <typename T>
Iterator<T>::Iterator(T* addr) : obj(addr)
{
}

template <typename T>
Iterator<T>::Iterator(const Iterator<T>& it) : obj(new T(it.obj))
{
}

template <typename T>
Iterator<T>::Iterator(Iterator<T>&& it) : obj(Meta::Move(it.obj))
{
}

template <typename T>
T*
Iterator<T>::get() noexcept
{
	return (this->obj);
}

/*
	ASSIGNMENT
*/

template <typename T>
Iterator<T>&	Iterator<T>::operator =(const Iterator<T>& it)
{
	if (this != &it)
		this->obj = it.obj;
	return (*this);
}

template <typename T>
Iterator<T>&	Iterator<T>::operator =(Iterator<T>&& it)
{
	if (this != &it)
	{
		this->obj = it.obj;
		it.obj = nullptr;
	}
	return (*this);
}

template <typename T>
Iterator<T>&	Iterator<T>::operator -=(const uint64& v)
{
	this->obj -= v;
	return (*this);
}

template <typename T>
Iterator<T>&	Iterator<T>::operator +=(const uint64& v)
{
	this->obj += v;
	return (*this);
}

template <typename T>
Iterator<T>&	Iterator<T>::operator -=(uint64&& v)
{
	this->obj -= Meta::Move(v);
	return (*this);
}

template <typename T>
Iterator<T>&	Iterator<T>::operator +=(uint64&& v)
{
	this->obj += Meta::Move(v);
	return (*this);
}

/*
	ARITHMETIC
*/

template <typename T>
Iterator<T>	Iterator<T>::operator -(uint64 v)
{
	return (Iterator<T>(this->obj - v));
}

template <typename T>
Iterator<T>	Iterator<T>::operator +(uint64 v)
{
	return (Iterator<T>(this->obj + v));
}

/*
	MEMBER ACCESS
*/

template <typename T>
Iterator<T>	Iterator<T>::operator [](const int& index)
{
	return (Iterator<T>(this->obj + index));
}

template <typename T>
Iterator<T>	Iterator<T>::operator [](int&& index)
{
	return (Iterator<T>(this->obj + Meta::Move(index)));
}

template <typename T>
T&	Iterator<T>::operator *()
{
	return (*this->obj);
}

template <typename T>
T*	Iterator<T>::operator ->()
{
	return (this->obj);
}

/*
	INCREMENT
	DECREMENT
*/

template <typename T>
Iterator<T>&	Iterator<T>::operator ++()
{
	++this->obj;
	return (*this);
}

template <typename T>
Iterator<T>	Iterator<T>::operator ++(int)
{
	Iterator<T> tmp = Iterator<T>(*this);
	++this->obj;
	return (tmp);
}
