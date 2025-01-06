/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_BARRIER_HPP
#define EGIDE_BARRIER_HPP

# include "String.hpp"
# include "Mutex.hpp"
# include "Meta.hpp"
# include <pthread.h>
# include <map>

// Create a barrier with a number, representing the number of threads that must wait for the barrier.
// This allows you to synchronize threads so that they wait for each other.
class Barrier
{
public:
	Barrier(const uint& count)	noexcept;
	~Barrier()					noexcept;

	int 	Wait()	noexcept;
	uint	GetNumberOfBarriers() const noexcept;

private:
	const uint			n;
	pthread_barrier_t	barrier;
};


// It's a simpler way to create Barrier and manage them.
class ManagedBarrier final : private Barrier
{
public:
	explicit ManagedBarrier()				= delete;
	explicit ManagedBarrier(const Barrier&)	= delete;
	explicit ManagedBarrier(Barrier&&)		= delete;
	virtual ~ManagedBarrier()				= delete;

	static void Create(const String& barrierID, const uint& count) noexcept;
	static void Create(const String& barrierID, uint&& count) noexcept;

	static void Wait(const String& barrierID);

	static void Destroy(const String& barrierID);

	using Barrier::GetNumberOfBarriers;
	static uint	GetNumberOfBarriers(const String& barrierID);

	class DoesNotExist
	{
	public:
		const char* what() const noexcept;
	};

private:
	static std::map<String, Barrier>	sync_barrier;
	static Mutex::Strict				sync_mutex;
};

#endif
