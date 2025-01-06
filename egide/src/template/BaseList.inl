#include "../BaseList.hpp"

template <typename T>
BaseList<T>::BaseList() noexcept : data(nullptr), size(0), first(Iterator<T>()), last(Iterator<T>())
{

}

template <typename T>
BaseList<T>::BaseList(const BaseList<T>& al) noexcept : data(new T[al.size]), size(al.size), first(al.first), last(al.last)
{
	for (uint64 i = 0ULL ; i < al.size ; i++)
		this->data[i] = al.data[i];
}

template <typename T>
BaseList<T>::BaseList(BaseList&& al) noexcept : data(Meta::Move(al.data)), size(Meta::Move(al.size)), first(Meta::Move(al.first)), last(Meta::Move(al.last))
{
	al.data = nullptr;
	al.size = 0;
}

template <typename T>
BaseList<T>::~BaseList() noexcept
{
	delete[] (this->data);
}

template <typename T>
uint64
BaseList<T>::Size() const noexcept
{
	return (this->size);
}



template <typename T>
Iterator<T>&
BaseList<T>::begin() noexcept
{
	return (this->first);
}

template <typename T>
Iterator<T>&
BaseList<T>::end() noexcept
{
	return (this->last);
}

template <typename T>
Iterator<const T>
BaseList<T>::cbegin() const noexcept
{
	return (static_cast<Iterator<const T>>(this->first));
}

template <typename T>
Iterator<const T>
BaseList<T>::cend() const noexcept
{
	return (static_cast<Iterator<const T>>(this->last));
}
