/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_SLEEP_HPP
#define NSL_SLEEP_HPP

# include "Async.hpp"

// Permet des opérations de sommeil sur n'importe quel thread (y compris le MainThread)
namespace Sleep
{
	// Like a while() but using less CPU cycles
	void	While(const bool&);
	// Like a while() but using less CPU cycles
	void	While(const bool&, Mutex& mtx);
	// Like a while() but using less CPU cycles
	void	While(const bool&, Mutex::Strict& mtx);

	// Like a while() but using less CPU cycles
	void	While(const int&);
	// Like a while() but using less CPU cycles
	void	While(const int&, Mutex& mtx);
	// Like a while() but using less CPU cycles
	void	While(const int&, Mutex::Strict& mtx);

	void	ForSeconds(unsigned long&& s);
	void	ForSeconds(const unsigned long& s);

	void	ForMilliS(unsigned long&& ms);
	void	ForMilliS(const unsigned long& ms);

	void	ForMicroS(unsigned long&& mcs);
	void	ForMicroS(const unsigned long& mcs);

	void	ForNanoS(unsigned long long&& ns);
	void	ForNanoS(const unsigned long long& ns);
}

/*
	THIS THREAD
*/

namespace ThisThread
{
	FORCEINLINE void	MakePause(unsigned int&& id_reference) noexcept
	{
		Thread::Async::MakePause(id_reference);
	}

	FORCEINLINE void	MakePause(const unsigned int& id_reference) noexcept
	{
		Thread::Async::MakePause(id_reference);
	}

	// Yield the CPU to an another thread.
	// Nice if you have very a lot of threads, otherwise use Thread::Asyns::LongYield()
	FORCEINLINE void	Yield() noexcept
	{
		Thread::Async::Yield();
	}

	// Much more efficient than Thread::Async::Yield() if there are not many threads
	FORCEINLINE void	LongYield() noexcept
	{
		Thread::Async::LongYield();
	}
}

/*
	OTHER THREAD
*/

namespace OtherThread
{
	FORCEINLINE void Play(unsigned int&& id) noexcept
	{
		Thread::Async::Play(id);
	}

	FORCEINLINE void Play(const unsigned int& id) noexcept
	{
		Thread::Async::Play(id);
	}

	FORCEINLINE void TryPlay(unsigned int&& id) noexcept
	{
		Thread::Async::TryPlay(id);
	}

	FORCEINLINE void TryPlay(const unsigned int& id) noexcept
	{
		Thread::Async::TryPlay(id);
	}
}

#endif
