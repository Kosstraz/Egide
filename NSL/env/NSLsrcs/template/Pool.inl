/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_POOL_INL
#define NSL_POOL_INL

#include "../Pool.hpp"

/************/
/*	POOL	*/
/************/

template <typename ... TArgs>
Pool::Pool(const TArgs& ... args) : size(0)
{
	(this->Add<TArgs>(args), ...);
}

template <typename T, typename ... TArgs>
Pool::Object<T>&	Pool::Acquire(TArgs&& ...p_args)
{
	Pool::Object<T>	ret;

	ret = new Pool::Object<T>(static_cast<TArgs&&>(p_args)...);
	this->Add(ret);
	return (ret);
}

template <typename T>
Pool::Object<T>&	Pool::Acquire(void)
{
	Pool::Object<T>	ret;

	ret = new Pool::Object<T>();
	this->Add(ret);
	return (ret);
}

template <typename T>
void	Pool::Add(const T& obj)
{
	this->size++;
	this->objects.emplace_back(SmartPtr<Object<T>>(new Object<T>(obj)));
}

template <typename T>
Pool::Object<T>*	Pool::At(unsigned int&& index)
{
	return (static_cast<Pool::Object<T>*>(this->objects[index].get()));
}

template <typename T>
Pool::Object<T>*	Pool::At(const unsigned int& index)
{
	return (static_cast<Pool::Object<T>*>(this->objects[index].get()));
}

/********************/
/*	POOL::OBJECT	*/
/********************/

template <typename T>
Pool::Object<T>::Object(const T& addConstRef)
{
	this->obj = addConstRef;
}

template <typename T>
Pool::Object<T>::operator T()
{
	return (this->obj);
}

#endif
