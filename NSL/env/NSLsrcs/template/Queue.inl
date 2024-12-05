#include "../Queue.hpp"

template<typename T>
Queue<T>::Queue() noexcept : BaseList<T>()
{
	
}

template<typename T>
Queue<T>::Queue(const Queue& q) noexcept : BaseList<T>(q)//data(new T[q.size]), size(q.size), first(data[0]), last(data[size - 1ULL])
{
	for (uint64 i = 0ULL ; i < this->size ; i++)
		this->data[i] = q.data;
}

template <typename T>
Queue<T>::Queue(Queue&& q) noexcept : BaseList<T>(Meta::Move(q))//data(Meta::Move(q.data)), size(Meta::Move(q.size)), first(Meta::Move(q.first)), last(Meta::Move(q.last))
{
}

template <typename T>
Queue<T>::~Queue() noexcept
{
	//delete[] (this->data);
}


template <typename T>
void
Queue<T>::Push(const T& elem) noexcept
{
	if (this->data)
	{
		T*	tmp = this->data;
		this->data = new T[this->size + 1ULL];
		this->first = this->data;
		for (uint64 i = 0ULL ; i < this->size ; i++)
			this->data[i] = tmp[i];
		delete[] (tmp);
	}
	else
	{
		this->data = new T[1ULL];
		this->first = this->data;
	}
	this->data[this->size] = elem;
	this->last = &this->data[this->size];
	this->size += 1ULL;
}

template <typename T>
void
Queue<T>::Push(T&& elem) noexcept
{
	if (this->data)
	{
		T*	tmp = this->data;
		this->data = new T[this->size + 1ULL];
		this->first = this->data;
		for (uint64 i = 0ULL ; i < this->size ; i++)
			this->data[i] = tmp[i];
		delete[] (tmp);
	}
	else
	{
		this->data = new T[1ULL];
		this->first = this->data;
	}
	this->data[this->size] = Meta::Move(elem);
	this->last = &this->data[this->size];
	this->size += 1ULL;
}

template <typename T>
void
Queue<T>::PushRef(T& elem_ref) noexcept
{
	if (this->data)
	{
		T*	tmp = this->data;
		this->data = new T[this->size + 1ULL];
		this->first = this->data;
		for (uint64 i = 0ULL ; i < this->size ; i++)
			this->data[i] = tmp[i];
		delete[] (tmp);
	}
	else
	{
		this->data = new T[1ULL];
		this->first = this->data;
	}
	this->data[this->size] = Meta::Forward<T&>(elem_ref);
	this->last = &this->data[this->size];
	this->size += 1ULL;
}

template <typename T>
T&&
Queue<T>::Pop() noexcept
{
	--this->size;
	++this->first;
	return (Meta::Move(*((this->first - 1ULL).get())));
}


/***********
 * 
 * 		OPERATORS
 * 
 */

template <typename T>
T&
Queue<T>::operator [](const int& index) noexcept
{
	return (this->data[index]);
}

template <typename T>
T&
Queue<T>::operator [](int&& index) noexcept
{
	return (this->data[Meta::Move(index)]);
}

template <typename T>
Queue<T>&
Queue<T>::operator =(Queue&& q) noexcept
{
	if (this != &q)
	{
		this->data = Meta::Move(q.data);
		this->size = Meta::Move(q.size);
		q.data = nullptr;
		q.size = 0ULL;
		return (*this);
	}
}

template <typename T>
Queue<T>&
Queue<T>::operator =(const Queue& q) noexcept
{
	if (this != &q)
	{
		if (this->size < q.size)
		{
			delete[] (this->data);
			this->data = new T[q.size];
		}
		this->size = q.size;
		for (uint64 i = 0ULL ; i < q.size ; i++)
			this->data[i] = q.data[i];
	}
	return (*this);
}
