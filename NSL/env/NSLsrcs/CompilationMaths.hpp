/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_COMPILATIONMATHS_HPP
#define NSL_COMPILATIONMATHS_HPP

# include "TypesCap.hpp"
# include "IOStreams.hpp"

// Allows heavy mathematical calculations to be performed during compilation
// Float & double calculations is not supported
namespace CMaths
{

typedef unsigned long long	cm_int64;

// Divide only ints
template <cm_int64 A, cm_int64 B>
static inline constexpr cm_int64	IntDivideBy = A / B;

// Divide only ints
template <cm_int64 A, cm_int64 B>
static inline constexpr cm_int64	FastIntDivideBy = A * (1 / B);

// Multiply only ints
template <cm_int64 A, cm_int64 B>
static inline constexpr cm_int64	IntMultiplyBy = A * B;



template <cm_int64 N, cm_int64 P>
requires Types::IsPositive<cm_int64, N> && Types::IsPositive<cm_int64, P>
struct PowerStruct final
{
	static inline constexpr	cm_int64	value = N * PowerStruct<N, P - 1ULL>::value;
};

template <cm_int64 P>
struct PowerStruct<1ULL, P>
{
	static inline constexpr	cm_int64	value = 1ULL;
};

template <cm_int64 P>
struct PowerStruct<0ULL, P>
{
	static inline constexpr	cm_int64	value = 0ULL;
};

template <cm_int64 N>
struct PowerStruct<N, 1ULL>
{
	static inline constexpr cm_int64	value = N;
};

template <cm_int64 N>
struct PowerStruct<N, 0ULL>
{
	static inline constexpr cm_int64	value = 1ULL;
};

template <cm_int64 N, cm_int64 P>
inline constexpr cm_int64	PowerOf = PowerStruct<N, P>::value;







template <cm_int64 N>
requires Types::IsPositive<cm_int64, N>
struct FactorialStruct final
{
	static inline constexpr cm_int64	value = N * FactorialStruct<N - 1ULL>::value;
};

template <>
struct FactorialStruct<0ULL>
{
	static inline constexpr cm_int64	value = 1ULL;
};

template <cm_int64 N>
inline constexpr cm_int64	FactorialOf = FactorialStruct<N>::value;

}

#endif
