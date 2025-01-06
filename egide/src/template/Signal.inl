#ifndef EGIDE_SIGNAL_INL
#define EGIDE_SIGNAL_INL

# include "../Signal.hpp"

template <typename TFun>
void
Signal::Listen(const Signum& sigcode, TFun&& fun) noexcept
{
	signal(static_cast<int>(sigcode), fun);
}
template <typename TFun>
void
Signal::Listen(Signum&& sigcode, TFun&& fun) noexcept
{
	signal(static_cast<int>(sigcode), fun);
}

void
Signal::Send(const Signum& sigcode, uint32 pid) noexcept
{
	kill(pid, static_cast<int>(sigcode));
}
void
Signal::Send(Signum&& sigcode, uint32 pid) noexcept
{
	kill(pid, static_cast<int>(sigcode));
}

void
Signal::Self(const Signum& sigcode) noexcept
{
	kill(Signal::ThisPID, static_cast<int>(sigcode));
}
void
Signal::Self(Signum&& sigcode) noexcept
{
	kill(Signal::ThisPID, static_cast<int>(sigcode));
}

void
Signal::SelfGroup(const Signum& sigcode) noexcept
{
	kill(Signal::ThisGPID, static_cast<int>(sigcode));
}
void
Signal::SelfGroup(Signum&& sigcode) noexcept
{
	kill(Signal::ThisGPID, static_cast<int>(sigcode));
}


void
Signal::SendToThisProcessGroup(const Signum& sigcode) noexcept
{
	kill(0, static_cast<int>(sigcode));
}
void
Signal::SendToThisProcessGroup(Signum&& sigcode) noexcept
{
	kill(0, static_cast<int>(sigcode));
}


void
Signal::SendToAllAuthorizedProccesses(const Signum& sigcode) noexcept
{
	kill(-1, static_cast<int>(sigcode));
}
void
Signal::SendToAllAuthorizedProccesses(Signum&& sigcode) noexcept
{
	kill(-1, static_cast<int>(sigcode));
}

void
Signal::SendToTheGroupOf(const Signum& sigcode, uint gpid) noexcept
{
	kill(-gpid, static_cast<int>(sigcode));
}
void
Signal::SendToTheGroupOf(Signum&& sigcode, uint gpid) noexcept
{
	kill(-gpid, static_cast<int>(sigcode));
}

#endif
