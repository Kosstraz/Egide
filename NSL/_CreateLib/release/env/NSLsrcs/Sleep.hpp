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

namespace ThisThread
{
	FORCEINLINE void MakePause(unsigned int&& id_reference)
	{
		Thread::Async::MakePause(id_reference);
	}

	FORCEINLINE void MakePause(const unsigned int& id_reference)
	{
		Thread::Async::MakePause(id_reference);
	}
}

namespace OtherThread
{
	FORCEINLINE void Play(unsigned int&& id)
	{
		Thread::Async::Play(id);
	}

	FORCEINLINE void Play(const unsigned int& id)
	{
		Thread::Async::Play(id);
	}

	FORCEINLINE void TryPlay(unsigned int&& id)
	{
		Thread::Async::TryPlay(id);
	}

	FORCEINLINE void TryPlay(const unsigned int& id)
	{
		Thread::Async::TryPlay(id);
	}
}

#endif
