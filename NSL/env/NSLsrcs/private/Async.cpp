#include "../Async.hpp"

std::map<uint, bool>
Thread::Async::async_pause = std::map<uint, bool>();

Mutex
Thread::Async::mutex = Mutex();

void
Thread::Async::MakePause(const uint& id) noexcept
{
	Thread::Async::mutex.Lock();
	if (Thread::Async::async_pause.contains(id))
		Thread::Async::async_pause.at(id) = true;
	else
		Thread::Async::async_pause.emplace(id, true);
	while (Thread::Async::async_pause.at(id) == true)
	{
		Thread::Async::mutex.Unlock();
		Thread::Async::mutex.Lock();
	}
	Thread::Async::mutex.Unlock();
}

void
Thread::Async::MakePause(uint&& id) noexcept
{
	Thread::Async::mutex.Lock();
	if (Thread::Async::async_pause.contains(Meta::Move(id)))
		Thread::Async::async_pause.at(Meta::Move(id)) = true;
	else
		Thread::Async::async_pause.emplace(Meta::Move(id), true);
	while (Thread::Async::async_pause.at(Meta::Move(id)) == true)
	{
		Thread::Async::mutex.Unlock();
		Thread::Async::mutex.Lock();
	}
	Thread::Async::mutex.Unlock();
}

void
Thread::Async::TryPlay(const uint& id) noexcept
{
	Thread::Async::mutex.Lock();
	if (Thread::Async::async_pause.contains(id))
		Thread::Async::async_pause.at(id) = false;
	Thread::Async::mutex.Unlock();
}

void
Thread::Async::TryPlay(uint&& id) noexcept
{
	Thread::Async::mutex.Lock();
	if (Thread::Async::async_pause.contains(Meta::Move(id)))
		Thread::Async::async_pause.at(Meta::Move(id)) = false;
	Thread::Async::mutex.Unlock();
}

void
Thread::Async::Play(const uint& id) noexcept
{
	Thread::Async::mutex.Lock();
	while (!Thread::Async::async_pause.contains(id))
	{
		Thread::Async::mutex.Unlock();
		Thread::Async::mutex.Lock();
	}
	Thread::Async::async_pause.at(id) = false;
	Thread::Async::mutex.Unlock();
}

void
Thread::Async::Play(uint&& id) noexcept
{
	Thread::Async::mutex.Lock();
	while (!Thread::Async::async_pause.contains(Meta::Move(id)))
	{
		Thread::Async::mutex.Unlock();
		Thread::Async::mutex.Lock();
	}
	Thread::Async::async_pause.at(Meta::Move(id)) = false;
	Thread::Async::mutex.Unlock();
}
