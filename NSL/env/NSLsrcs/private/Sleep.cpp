#include "../Sleep.hpp"

void
Sleep::While(const bool& c)
{
	while (c)
		Thread::Async::LongYield();
}

void
Sleep::While(const bool& c, Mutex& mtx)
{
	mtx.Lock();
	while (c)
	{
		mtx.Unlock();
		Thread::Async::LongYield();
		mtx.Lock();
	}
	mtx.Unlock();
}

void
Sleep::While(const bool& c, Mutex::Strict& mtx)
{
	mtx.RLock();
	while (c)
	{
		mtx.Unlock();
		Thread::Async::LongYield();
		mtx.RLock();
	}
	mtx.Unlock();
}

void
Sleep::While(const int& c)
{
	while (c)
		Thread::Async::LongYield();
}
void
Sleep::While(const int& c, Mutex& mtx)
{
	mtx.Lock();
	while (c)
	{
		mtx.Unlock();
		Thread::Async::LongYield();
		mtx.Lock();
	}
	mtx.Unlock();
}
void
Sleep::While(const int& c, Mutex::Strict& mtx)
{
	mtx.RLock();
	while (c)
	{
		mtx.Unlock();
		Thread::Async::LongYield();
		mtx.RLock();
	}
	mtx.Unlock();
}

void
Sleep::ForSeconds(unsigned long&& s)
{
	timespec	ts;
	ts.tv_sec = Meta::Move(s);
	ts.tv_nsec = 0;
	nanosleep(&ts, nullptr);
}

void
Sleep::ForSeconds(const unsigned long& s)
{
	timespec	ts;
	ts.tv_sec = s;
	ts.tv_nsec = 0;
	nanosleep(&ts, nullptr);
}

void
Sleep::ForMilliS(unsigned long&& ms)
{
	timespec	ts;
	ts.tv_sec = 0;
	ts.tv_nsec = Meta::Move(ms) * 1000000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec	+= ts.tv_nsec / 1000000000;
		ts.tv_nsec	= ts.tv_nsec % 1000000000;
	}
	nanosleep(&ts, nullptr);
}

void
Sleep::ForMilliS(const unsigned long& ms)
{
	timespec	ts;
	ts.tv_sec = 0;
	ts.tv_nsec = ms * 1000000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec	+= ts.tv_nsec / 1000000000;
		ts.tv_nsec	= ts.tv_nsec % 1000000000;
	}
	nanosleep(&ts, nullptr);
}

void
Sleep::ForMicroS(unsigned long&& mcs)
{
	timespec	ts;
	ts.tv_sec = 0;
	ts.tv_nsec = Meta::Move(mcs) * 1000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec	+= ts.tv_nsec / 1000000000;
		ts.tv_nsec	= ts.tv_nsec % 1000000000;
	}
	nanosleep(&ts, nullptr);
}

void
Sleep::ForMicroS(const unsigned long& mcs)
{
	timespec	ts;
	ts.tv_sec = 0;
	ts.tv_nsec = mcs * 1000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec	+= ts.tv_nsec / 1000000000;
		ts.tv_nsec	= ts.tv_nsec % 1000000000;
	}
	nanosleep(&ts, nullptr);
}

void
Sleep::ForNanoS(unsigned long long&& ns)
{
	timespec	ts;
	ts.tv_sec = 0;
	ts.tv_nsec = Meta::Move(ns);
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec	+= ts.tv_nsec / 1000000000;
		ts.tv_nsec	= ts.tv_nsec % 1000000000;
	}
	nanosleep(&ts, nullptr);
}

void
Sleep::ForNanoS(const unsigned long long& ns)
{
	timespec	ts;
	ts.tv_sec = 0;
	ts.tv_nsec = ns;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec	+= ts.tv_nsec / 1000000000;
		ts.tv_nsec	= ts.tv_nsec % 1000000000;
	}
	nanosleep(&ts, nullptr);
}
