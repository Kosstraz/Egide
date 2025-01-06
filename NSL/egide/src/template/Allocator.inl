/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_ALLOCATOR_INL
#define EGIDE_ALLOCATOR_INL

# include <new>
# include "../Allocator.hpp"

	/*******************/
	/*	CONSTRUCTIONS  */
	/*******************/

template <typename T>
constexpr T*
Allocator<T>::Construct(unsigned int&& n)
{
	return (new T[n]);
}

template <typename T>
constexpr T*
Allocator<T>::Construct(const unsigned int& n)
{
	return (new T[n]);
}

template <typename T>
constexpr void
Allocator<T>::Deconstruct(T* ptr)
{
	delete[] ptr;
}


# if __cpp_aligned_new
template <typename T>
constexpr T*
Allocator<T>::ConstructAlign(unsigned int&& n)
{
	T*	ret;

	if (n > __BIGGEST_ALIGNMENT__)
		ret = static_cast<T*>(::operator new[](n, std::align_val_t{__BIGGEST_ALIGNMENT__}));
	else
		ret = static_cast<T*>(::operator new[](n, std::align_val_t{n * sizeof(T)}));
	for (unsigned int i = 0 ; i < n ; i++)
		new (&ret[i]) T();
	return (ret);
}

template <typename T>
constexpr T*
Allocator<T>::ConstructAlign(const unsigned int& n)
{
	T*	ret;

	if (n > __BIGGEST_ALIGNMENT__)
		ret = static_cast<T*>(::operator new[](n, std::align_val_t{__BIGGEST_ALIGNMENT__}));
	else
		ret = static_cast<T*>(::operator new[](n, std::align_val_t{n * sizeof(T)}));
	for (unsigned int i = 0 ; i < n ; i++)
		ret[i] = T();
	return (ret);
}

template <typename T>
constexpr void
Allocator<T>::DeconstructAlign(T* __restrict ptr, const unsigned int& tabSize)
{
	for (unsigned int i = 0 ; i < tabSize ; i++)
		ptr[i].~T();
	::operator delete[](ptr, tabSize);
}

template <typename T>
constexpr void
Allocator<T>::DeconstructAlign(T* __restrict ptr, unsigned int&& tabSize)
{
	for (unsigned int i = 0 ; i < tabSize ; i++)
		ptr[i].~T();
	::operator delete[](ptr, tabSize);
}
# endif

	/*****************/
	/*	ALLOCATIONS  */
	/*****************/

template <typename T>
constexpr T*
Allocator<T>::ALLOC_(unsigned int&& n)
{
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n))));
}

template <typename T>
constexpr T*
Allocator<T>::ALLOC_(const unsigned int& n)
{
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n))));
}

template <typename T>
constexpr void
Allocator<T>::DEALLOC_(T* ptr)
{
	::operator delete[](ptr);//_mm_free(ptr);
}


# if __cpp_aligned_new
template <typename T>
constexpr T*
Allocator<T>::ALLOC_(unsigned int&& n, const unsigned long& align)
{
	unsigned long	alignSize 	= align;
	if (alignSize >= __BIGGEST_ALIGNMENT__)
		alignSize = static_cast<unsigned long>(__BIGGEST_ALIGNMENT__);
	else if (alignSize == 0)
		alignSize = static_cast<unsigned long>(1);
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n),
			std::align_val_t{alignSize * sizeof(T)})));
	//return (static_cast<T*>(_mm_malloc(n, align)));
}

template <typename T>
constexpr T*
Allocator<T>::ALLOC_(const unsigned int& n, const unsigned long& align)
{
	unsigned long	alignSize 	= align;
	if (alignSize >=  __BIGGEST_ALIGNMENT__)
		alignSize = static_cast<unsigned long>(__BIGGEST_ALIGNMENT__);
	else if (alignSize == 0)
		alignSize = static_cast<unsigned long>(1);
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n),
			std::align_val_t{alignSize * sizeof(T)})));
	//return (static_cast<T*>(_mm_malloc(n, align)));
}

template <typename T>
constexpr void
Allocator<T>::DEALLOC_(T* ptr, const unsigned long&& align)
{
	unsigned long	alignSize 	= align;
	if (alignSize >=  __BIGGEST_ALIGNMENT__)
		alignSize = static_cast<unsigned long>(__BIGGEST_ALIGNMENT__);
	else if (alignSize == 0)
		alignSize = static_cast<unsigned long>(1);
	::operator delete[](ptr, std::align_val_t{alignSize * sizeof(T)});
}

template <typename T>
constexpr void
Allocator<T>::DEALLOC_(T* ptr, const unsigned long& align)
{
	unsigned long	alignSize 	= align;
	if (alignSize >=  __BIGGEST_ALIGNMENT__)
		alignSize = static_cast<unsigned long>(__BIGGEST_ALIGNMENT__);
	else if (alignSize == 0)
		alignSize = static_cast<unsigned long>(1);
	::operator delete[](ptr, std::align_val_t{alignSize * sizeof(T)});
}
# endif


	/*********************/
	/*	HOT_ALLOCATIONS  */
	/*********************/


template <typename T>
constexpr T*
Allocator<T>::ALLOC_HOT(unsigned int&& n)
{
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n))));
}

template <typename T>
constexpr T*
Allocator<T>::ALLOC_HOT(const unsigned int& n)
{
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n))));
}

template <typename T>
constexpr void
Allocator<T>::DEALLOC_HOT(T* ptr)
{
	::operator delete(ptr);
}


# if __cpp_aligned_new
template <typename T>
constexpr T*
Allocator<T>::ALLOC_HOT(unsigned int&& n, const unsigned long& align)
{
	const long maxAlign			= sysconf(_SC_PAGE_SIZE);
	unsigned long	alignSize 	= align;
	if (alignSize >= maxAlign)
		alignSize = static_cast<unsigned long>(maxAlign - 1);
	else if (alignSize == 0)
		alignSize = static_cast<unsigned long>(1);
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n),
			std::align_val_t{alignSize * sizeof(T)})));
}

template <typename T>
constexpr T*	
Allocator<T>::ALLOC_HOT(const unsigned int& n, const unsigned long& align)
{
	const long maxAlign			= sysconf(_SC_PAGE_SIZE);
	unsigned long	alignSize 	= align;

	if (alignSize >=  maxAlign)
		alignSize = static_cast<unsigned long>(maxAlign - 1);
	else if (alignSize == 0)
		alignSize = static_cast<unsigned long>(1);
	return (static_cast<T*>(::operator new[](static_cast<__uint128_t>(sizeof(T)) * static_cast<__uint128_t>(n),
			std::align_val_t{alignSize * sizeof(T)})));
}

template <typename T>
constexpr void
Allocator<T>::DEALLOC_HOT(T* ptr, unsigned long&& align)
{
	const long maxAlign	= sysconf(_SC_PAGE_SIZE);
	if (align >=  maxAlign)
		align = static_cast<unsigned long>(maxAlign - 1);
	else if (align == 0)
		align = static_cast<unsigned long>(1);
	::operator delete[](ptr, std::align_val_t{align * sizeof(T)});
}

template <typename T>
constexpr void
Allocator<T>::DEALLOC_HOT(T* ptr, const unsigned long& align)
{
	long maxAlign	= sysconf(_SC_PAGE_SIZE);
	if (align >=  maxAlign)
		maxAlign = static_cast<unsigned long>(maxAlign - 1);
	else if (align == 0)
		maxAlign = static_cast<unsigned long>(1);
	::operator delete[](ptr, std::align_val_t{maxAlign * sizeof(T)});
}
# endif

#endif
