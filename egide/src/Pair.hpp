#ifndef EGIDE_PAIR_HPP
#define EGIDE_PAIR_HPP

# include "../egide_platform.h"
# include "TypesCap.hpp"

// A structure containing 2 elements
//
// If you want more elements, check the Trio struct (or Package struct)
template <typename T1, typename T2>
struct Pair
{
private:
	typedef Decay<T1>	_T1;
	typedef Decay<T2>	_T2;

public:
	constexpr	Pair() noexcept : a(), b()
	{
	}

	constexpr	Pair(T1&& pA, const T2& pB) noexcept : a(Meta::Forward<T1>(pA)), b(_T2(pB))
	{
	}

	constexpr	Pair(const T1& pA, T2&& pB) noexcept : a(_T1(pA)), b(Meta::Forward<T2>(pB))
	{
	}

	constexpr	Pair(const T1& pA, const T2& pB) noexcept : a(_T1(pA)), b(_T2(pB))
	{
	}

	constexpr	Pair(T1&& pA, T2&& pB) noexcept : a(Meta::Forward<T1>(pA)), b(Meta::Forward<T2>(pB))
	{
	}

	virtual FORCEINLINE	~Pair()
	{
	}

	_T1	a;
	_T2	b;
};


#endif
