/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_STRING_HPP
#define NSL_STRING_HPP

# ifndef MALLOC_ATTR
#  define MALLOC_ATTR __attribute__((malloc))
# endif

# define STRING_PREALLOC_SIZE	100ULL

# include "Meta.hpp"
# include "../NSLSIMDplatform.h"
# include "../NSLplatform.h"
# include "Allocator.hpp"
# include <string> // just for the conversion between String AND std::string

// A String class
//
// Todo: .Find()
// Todo: .FindFirstOf()
// Todo: .FindLastOf()
// Todo: .FindNotFirstOf()
// Todo: .FindNotLastOf()
// Todo: .Insert()  --> char & String
class String final
{
public:
	String();
	String(const std::string& str_cpy);
	String(const String& str_cpy);
	String(const char* data);
	~String();

	inline bool	Contains(const char* data)	const;
	inline bool	Contains(const String& str)	const;

	constexpr int	CompareWith(const char* data)	const;
	constexpr int	CompareWith(const String& str)	const;
	constexpr int	CompareNByteWith(const char* data, unsigned int n)	const;
	constexpr int	CompareNByteWith(const String& str, unsigned int n)	const;

	constexpr bool	IsEqualWith(const char* data)	const;
	constexpr bool	IsEqualWith(const String& str)	const;
	constexpr bool	IsNByteEqualWith(const char* data, unsigned int n)	const;
	constexpr bool	IsNByteEqualWith(const String& str, unsigned int n)	const;

	FORCEINLINE void	Reserve(const uint64& nbyte)	noexcept;

	// Equivalent to .Overwrite()
	FORCEINLINE void	Replace(const char* data)		noexcept;
		// Equivalent to .Overwrite()
	FORCEINLINE void	Replace(const String& str)		noexcept;
	// Equivalent to .Replace()
	FORCEINLINE void	Overwrite(const char*  data)	noexcept;
	// Equivalent to .Replace()
	FORCEINLINE void	Overwrite(const String& str)	noexcept;

	// Equivalent to .Join()
	FORCEINLINE void	Append(const char* data)	noexcept;
	// Equivalent to .Join()
	FORCEINLINE void	Append(const String& str)	noexcept;
	// Equivalent to .Append()
	FORCEINLINE void	Join(const char* data)		noexcept;
	// Equivalent to .Append()
	FORCEINLINE void	Join(const String& str)		noexcept;

	// Return -1 if the string is null
	// Calcul the length for each call (use Size() instead)
	[[nodiscard]]
	inline uint64	Len() const noexcept;
	// Return -1 if the string is null
	// Like Len(), but Size() doesn't recalculate the length if it has already been calculated
	[[nodiscard]]
	inline uint64	Size() const noexcept;

	// Return -1 if the string is null
	// Calcul the length for each call (use Size() instead)
	[[nodiscard]]
	static inline uint64	Len(const String& str) noexcept;
	// Return -1 if the string is null
	// Like Len(), but Size() doesn't recalculate the length if it has already been calculated
	[[nodiscard]]
	static inline uint64	Size(String& str) noexcept;

	[[nodiscard]]
	static inline uint64	Size(const char* cstr) noexcept;


	// (static) Return a new allocated string equal to the string.Data() in parameter
	// !(ne pas oublier de 'delete[]')!
	[[nodiscard]]
	static inline char*	CString(const String&)	noexcept MALLOC_ATTR;
	// Return a new allocated string equal to this string .Data()
	// !(ne pas oublier de 'delete[]')!
	[[nodiscard]]
	inline char*		CString()				noexcept MALLOC_ATTR;

	inline void				Swap(String&)		  noexcept;
	inline void				Shuffle()			  noexcept;
	inline void				Erase(const int& idex)		  noexcept;
	inline bool				Empty()			const;
	constexpr const char*	Data()			const noexcept;
	constexpr const char&	At(int index)	const noexcept;
	inline const char&		First()			const noexcept;
	inline const char&		Last()			const noexcept;
	// Equivalent to .Destroy()
	inline void			Clear()				  noexcept;
	// Equivalent to .Clear()
	inline void			Destroy()		 	  noexcept;

private:
	FORCEINLINE void
	_setSize_(uint64 newSize)		noexcept;

	FORCEINLINE void
	__join__(const String& str)		noexcept;

	FORCEINLINE void
	__replace__(const String& str)	noexcept;

	FORCEINLINE uint64
	__length__()			  const noexcept;

	FORCEINLINE static uint64
	__length__(const String& str)					noexcept;

	FORCEINLINE static uint64
	__length__(const char* cstr)					noexcept;

	FORCEINLINE static void
	__ncopy__ (char* dest, const char* src, const uint64 nbyte)	noexcept;

public:
	constexpr char&			operator[](int index)	const noexcept;
	constexpr				operator const char*()	const noexcept;

	constexpr bool			operator<(const String& str)	const noexcept;
	constexpr bool			operator>(const String& str)	const noexcept;
	constexpr bool			operator<=(const String& str)	const noexcept;
	constexpr bool			operator>=(const String& str)	const noexcept;
	constexpr bool			operator==(const String& str)	const noexcept;
	constexpr int			operator<=>(const String& str)	const noexcept;
	constexpr bool			operator!=(const String& str)	const noexcept;

	inline String	operator+(const String& str)			const noexcept;
	inline String	operator*(const unsigned int& count)	const noexcept;

	inline String&	operator=(const String& str)			noexcept;
	inline String&	operator+=(const String& str)			noexcept;
	inline String&	operator*=(const unsigned int& count)	noexcept;

private:
	char*	data;
	uint64	size;
	uint64	capacity;
	bool	allocated;
};

# include "template/String.inl"
# include "template/String_op.inl"
#endif
