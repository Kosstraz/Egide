#include "../Barrier.hpp"

Barrier::Barrier(const uint& count) noexcept : n(count)
{
	pthread_barrier_init(&this->barrier, nullptr, count);
}

Barrier::~Barrier() noexcept
{
	pthread_barrier_destroy(&this->barrier);
}

int
Barrier::Wait() noexcept
{
	return (pthread_barrier_wait(&this->barrier));
}

uint
Barrier::GetNumberOfBarriers() const noexcept
{
	return (this->n);
}
