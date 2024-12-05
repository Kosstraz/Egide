/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../Mutex.hpp"

Mutex::Strict::Strict() noexcept
{
	pthread_rwlock_init(&this->mutex, nullptr);
}

Mutex::Strict::~Strict() noexcept
{
	pthread_rwlock_destroy(&this->mutex);
}

void
Mutex::Strict::Destroy()
{
	pthread_rwlock_destroy(&this->mutex);
}

int
Mutex::Strict::TryRLock()
{
	return (pthread_rwlock_tryrdlock(&this->mutex));
}

void
Mutex::Strict::TimedRLock(unsigned int seconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += seconds;
	ts.tv_nsec = 0;
	pthread_rwlock_timedrdlock(&this->mutex, &ts);
}

void
Mutex::Strict::TimedRLock(unsigned long mseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += mseconds / 1000;
	ts.tv_nsec = 0;
	pthread_rwlock_timedrdlock(&this->mutex, &ts);
}

void
Mutex::Strict::TimedRLock(unsigned long long nseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_nsec += nseconds;
	if (nseconds >= 1000000000)
	{
		ts.tv_sec += ts.tv_nsec / 1000000000;
		ts.tv_nsec = ts.tv_nsec % 1000000000;
	}
	pthread_rwlock_timedrdlock(&this->mutex, &ts);
}

void
Mutex::Strict::RLock() noexcept
{
	pthread_rwlock_rdlock(&this->mutex);
}

int
Mutex::Strict::TryWRLock()
{
	return (pthread_rwlock_trywrlock(&this->mutex));
}

void
Mutex::Strict::TimedWRLock(unsigned int seconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += seconds;
	ts.tv_nsec = 0;
	pthread_rwlock_timedwrlock(&this->mutex, &ts);
}

void
Mutex::Strict::TimedWRLock(unsigned long mseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += mseconds / 1000;
	ts.tv_nsec = 0;
	pthread_rwlock_timedwrlock(&this->mutex, &ts);
}

void
Mutex::Strict::TimedWRLock(unsigned long long nseconds) noexcept
{
	struct timespec	ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_nsec += nseconds;
	if (nseconds >= 1000000000)
	{
		ts.tv_sec += ts.tv_nsec / 1000000000;
		ts.tv_nsec = ts.tv_nsec % 1000000000;
	}
	pthread_rwlock_timedwrlock(&this->mutex, &ts);
}

void
Mutex::Strict::WRLock() noexcept
{
	pthread_rwlock_wrlock(&this->mutex);
}

void
Mutex::Strict::Unlock() noexcept
{
	pthread_rwlock_unlock(&this->mutex);
}
