#include "../Barrier.hpp"

std::map<String, Barrier>
ManagedBarrier::sync_barrier = std::map<String, Barrier>();

Mutex::Strict
ManagedBarrier::sync_mutex = Mutex::Strict();

void
ManagedBarrier::Create(const String& barrierID, const uint& count) noexcept
{
	ManagedBarrier::sync_mutex.WRLock();
	ManagedBarrier::sync_barrier.emplace(barrierID, Barrier(count));
	ManagedBarrier::sync_mutex.Unlock();
}

void
ManagedBarrier::Create(const String& barrierID, uint&& count) noexcept
{
	ManagedBarrier::sync_mutex.WRLock();
	ManagedBarrier::sync_barrier.emplace(barrierID, Barrier(Meta::Move(count)));
	ManagedBarrier::sync_mutex.Unlock();
}

void
ManagedBarrier::Wait(const String& barrierID)
{
	ManagedBarrier::sync_mutex.RLock();
	try
	{
		Barrier& b = ManagedBarrier::sync_barrier.at(barrierID);
		ManagedBarrier::sync_mutex.Unlock();
		b.Wait();
	}
	catch (...)
	{
		ManagedBarrier::sync_mutex.Unlock();
		throw (ManagedBarrier::DoesNotExist());
	}
}

void
ManagedBarrier::Destroy(const String& barrierID)
{
	ManagedBarrier::sync_mutex.WRLock();
	try
	{
		ManagedBarrier::sync_barrier.erase(barrierID);
		ManagedBarrier::sync_mutex.Unlock();
	}
	catch (...)
	{
		ManagedBarrier::sync_mutex.Unlock();
		throw (ManagedBarrier::DoesNotExist());
	}
}

uint
ManagedBarrier::GetNumberOfBarriers(const String& barrierID)
{
	uint	ret;

	ManagedBarrier::sync_mutex.RLock();
	try
	{
		ret = static_cast<uint>(ManagedBarrier::sync_barrier.at(barrierID).GetNumberOfBarriers());
		ManagedBarrier::sync_mutex.Unlock();
	}
	catch (...)
	{
		ManagedBarrier::sync_mutex.Unlock();
		throw (ManagedBarrier::DoesNotExist());
	}
	return (ret);
}

const char*
ManagedBarrier::DoesNotExist::what() const noexcept
{
	return ("BarrierID specified does not exist!");
}
