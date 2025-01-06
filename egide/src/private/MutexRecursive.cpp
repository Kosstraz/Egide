#include "../Mutex.hpp"

Mutex::Recursive::Recursive() noexcept
{
	this->mutex = { { 0, 0, 0, 0, PTHREAD_MUTEX_RECURSIVE_NP, 0, 0, { 0, 0 } } };
}

Mutex::Recursive::~Recursive() noexcept
{
	pthread_mutex_destroy(&this->mutex);
}

void
Mutex::Recursive::Destroy()
{
	pthread_mutex_destroy(&this->mutex);
}

int	
Mutex::Recursive::TryLock()
{
	return (pthread_mutex_trylock(&this->mutex));
}

void
Mutex::Recursive::TimedLock(unsigned int seconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += seconds;
	ts.tv_nsec = 0;
	pthread_mutex_timedlock(&this->mutex, &ts);
}

void
Mutex::Recursive::TimedLock(unsigned long mseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += mseconds / 1000;
	ts.tv_nsec = 0;
	pthread_mutex_timedlock(&this->mutex, &ts);
}

void
Mutex::Recursive::TimedLock(unsigned long long nseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_nsec += nseconds;
	if (nseconds >= 1000000000)
	{
		ts.tv_sec += ts.tv_nsec / 1000000000;
		ts.tv_nsec = ts.tv_nsec % 1000000000;
	}
	pthread_mutex_timedlock(&this->mutex, &ts);
}

void
Mutex::Recursive::Lock() noexcept
{
	pthread_mutex_lock(&this->mutex);
}

void
Mutex::Recursive::Unlock() noexcept
{
	pthread_mutex_unlock(&this->mutex);
}
