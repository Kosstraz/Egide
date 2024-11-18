/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_TRIO_HPP
#define NSL_TRIO_HPP

# include "../NSLplatform.h"
# include "TypesCap.hpp"

// A structure containing 3 elements
//
// If you want less elements, check the Pair struct
// If you want more elements, check the Package struct
template <typename T1, typename T2, typename T3>
struct Trio
{
private:
	typedef Decay<T1>	_T1;
	typedef Decay<T2>	_T2;
	typedef Decay<T3>	_T3;

public:
	constexpr	Trio() noexcept : a(), b(), c()
	{
	}

	constexpr	Trio(const T1& a, const T2& b, const T3& c) noexcept : a(_T1(a)), b(_T2(b)), c(_T3(c))
	{
	}

	constexpr	Trio(T1&& a, T2&& b, T3&& c) noexcept : a(Meta::Forward<T1>(a)), b(Meta::Forward<T2>(b)), c(Meta::Forward<T3>(c))
	{
	}

	virtual FORCEINLINE	~Trio()
	{
	}

	_T1	a;
	_T2	b;
	_T3	c;
};


#endif
