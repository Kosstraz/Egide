/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../Mutex.hpp"

Mutex::Mutex() noexcept
{
	pthread_mutex_init(&this->mutex, nullptr);
}

Mutex::~Mutex() noexcept
{
	pthread_mutex_destroy(&this->mutex);
}

void
Mutex::Destroy()
{
	pthread_mutex_destroy(&this->mutex);
}

int	
Mutex::TryLock()
{
	return (pthread_mutex_trylock(&this->mutex));
}

void
Mutex::TimedLock(unsigned int seconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += seconds;
	ts.tv_nsec = 0;
	pthread_mutex_timedlock(&this->mutex, &ts);
}

void
Mutex::TimedLock(unsigned long mseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += mseconds / 1000;
	ts.tv_nsec = 0;
	pthread_mutex_timedlock(&this->mutex, &ts);
}

void
Mutex::TimedLock(unsigned long long nseconds) noexcept
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
Mutex::Lock() noexcept
{
	pthread_mutex_lock(&this->mutex);
}

void
Mutex::Unlock() noexcept
{
	pthread_mutex_unlock(&this->mutex);
}
