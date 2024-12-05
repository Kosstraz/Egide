/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_ALLOCATOR_HPP
#define NSL_ALLOCATOR_HPP

# ifndef MALLOC_ATTR
#  define MALLOC_ATTR __attribute__((malloc))
# endif

# ifdef _WIN32
#  include <windows.h>
#  define __INIT_MEMORYPAGE_SIZE__	constexpr SYSTEM_INFO __ALLOCATOR_systemInfo__; GetSystemInfo(&__ALLOCATOR_systemInfo__);
#  define __GET_MEMORYPAGE_SIZE__	__ALLOCATOR_systemInfo__.dwPageSize;
# elif __linux__
#  include <unistd.h>
#  define __INIT_MEMORYPAGE_SIZE__	//only windows (because is shit)
#  define __GET_MEMORYPAGE_SIZE__	sysconf(_SC_PAGE_SIZE)
# else
	// Goodbye macEZ !
# endif

# include "../NSLplatform.h"

# ifdef ALLOCATORT_NAMES
#  define ALLOC_		Allocate
#  define DEALLOC_		Deallocate

# define ALLOC_HOT		HotAllocate
# define DEALLOC_HOT	HotDeallocate
# else
#  define ALLOC_		Reserve
#  define DEALLOC_		Free

# define ALLOC_HOT		HotReserve
# define DEALLOC_HOT	HotFree
# endif

// Difference between HotReserve/HotFree & Reserve/Free is minimal
// Check execution time and see if there is a big change
//
// You can define ALLOCATORT_NAMES if you prefere member methods with another names (Allocate/Deallocate instead of Reserve/Free)
template <typename T>
class Allocator final
{
public:
	Allocator()					= delete;
	Allocator(const Allocator&)	= delete;
	Allocator(Allocator&&)		= delete;
	virtual ~Allocator()		= default;

	/*******************/
	/*	CONSTRUCTIONS  */
	/*******************/

public:
	[[nodiscard]]
	FORCEINLINE static constexpr T*	Construct(unsigned int&& tabSize)		MALLOC_ATTR;
	[[nodiscard]]
	FORCEINLINE static constexpr T*	Construct(const unsigned int& tabSize)	MALLOC_ATTR;

	FORCEINLINE static constexpr void	Deconstruct(T* __restrict ptr);

public:
# if __cpp_aligned_new
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ConstructAlign(unsigned int&& tabSize)			MALLOC_ATTR;
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ConstructAlign(const unsigned int& tabSize)	MALLOC_ATTR;

	FORCEINLINE static constexpr void	DeconstructAlign(T* __restrict ptr, const unsigned int& tabSize);
	FORCEINLINE static constexpr void	DeconstructAlign(T* __restrict ptr, unsigned int&& tabSize);
#endif


	/*****************/
	/*	ALLOCATIONS  */
	/*****************/

public:
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_(unsigned int&& tabSize)		MALLOC_ATTR;
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_(const unsigned int& tabSize)	MALLOC_ATTR;

	FORCEINLINE static constexpr void	DEALLOC_(T* __restrict ptr);

public:
# if __cpp_aligned_new
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_(unsigned int&& size, const unsigned long& nByteAligned)			MALLOC_ATTR;
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_(const unsigned int& size, const unsigned long& nByteAligned)	MALLOC_ATTR;

	FORCEINLINE static constexpr void	DEALLOC_(T* __restrict ptr, const unsigned long&& nByteAligned);
	FORCEINLINE static constexpr void	DEALLOC_(T* __restrict ptr, const unsigned long& nByteAligned);
#endif

	/*********************/
	/*	HOT_ALLOCATIONS  */
	/*********************/

public:
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_HOT(unsigned int&& tabSize)		MALLOC_ATTR __attribute__((hot));
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_HOT(const unsigned int& tabSize)	MALLOC_ATTR __attribute__((hot));

	FORCEINLINE static constexpr void	DEALLOC_HOT(T* __restrict ptr)					__attribute__((hot));

public:
# if __cpp_aligned_new
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_HOT(unsigned int&& tabSize, const unsigned long& numberOfObjectsAlignedInMemory)		MALLOC_ATTR __attribute__((hot));
	[[nodiscard]]
	FORCEINLINE static constexpr T*	ALLOC_HOT(const unsigned int& tabSize, const unsigned long& numberOfObjectsAlignedInMemory)	MALLOC_ATTR __attribute__((hot));

	FORCEINLINE static constexpr void	DEALLOC_HOT(T* __restrict ptr, unsigned long&& numberOfObjectsAlignedInMemory);
	FORCEINLINE static constexpr void	DEALLOC_HOT(T* __restrict ptr, const unsigned long& numberOfObjectsAlignedInMemory);
#endif
};

# include "template/Allocator.inl"
#endif
