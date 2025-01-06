#ifndef EGIDE_SIGNAL_HPP
#define EGIDE_SIGNAL_HPP

# include "../egide_platform.h"
# include "Function.hpp"
# include <csignal>
# include <unistd.h>

enum struct Signum
{
	HangUp					= SIGHUP,	// Hang up controlling terminal or process
	CtrlZ					= SIGSTOP,	// Equivalent to Signum::Stop
	CtrlC					= SIGINT,	// Equivalent to Signum::Interrupt
	Interrupt				= SIGINT,	// Interrupt from keyboard --> ctrl + C
	Quit					= SIGQUIT,	//* Quit from keyboard --> ctrl + \	*/
	IllegalInstr			= SIGILL,	// Illegal instruction
	Breakpoint				= SIGTRAP,	// Breakpoint for debugging ! NO POSIX !
	Abort					= SIGABRT,	// Abnormal termination
	BusError				= SIGBUS,	// Bus error ! NO POSIX !
	FPE						= SIGFPE,	// Floating-point exception
	Kill					= SIGKILL,	// Forced-process termination
	User1					= SIGUSR1,	// Available to processes
	User2					= SIGUSR2,	// Available to processes
	InvalidMemRef			= SIGSEGV,	// Invalid memory reference
	Pipe					= SIGPIPE,	// Write to pipe with no readers
	TimerClock				= SIGALRM,	// Real-timer clock
	Terminate				= SIGTERM,	// Process termination
	CoprocStackErr			= SIGSTKFLT,// Coprocessor stack error ! NO POSIX !
	TryStopChild			= SIGCHLD,	// Child process stopped or terminated or got a signal if traced
	ResumeExecution			= SIGCONT,	// Resume execution, if stopped
	Stop					= SIGSTOP,	// Stop process execution --> ctrl + Z
	StopFromTTY				= SIGTSTP,	// Stop process issued from tty
	RequiresInput			= SIGTTIN,	// Background process requires input
	RequiresOutput			= SIGTTOU,	// Background process requires output
	UrgentOnSocket			= SIGURG,	// Urgent condition on socket ! NO POSIX !
	CPUTimeLimitExceeded	= SIGXCPU,	// CPU time limit exceeded ! NO POSIX !
	FileSizeLimitExceeded	= SIGXFSZ,	// File size limit exceeded ! NO POSIX !
	VirtualTimerClock		= SIGVTALRM,// Virtual timer clock ! NO POSIX !
	ProfileTimerClock		= SIGPROF,	// Profile timer clock ! NO POSIX !
	WindowResizing			= SIGWINCH,	// Window resizing ! NO POSIX !
	InOutNowAllowed			= SIGIO,	// I/O now possible ! NO POSIX !
	Poll					= SIGPOLL,	// Equivalent to SIGIO ! NO POSIX !
	PowerSupplyFailure		= SIGPWR,	// Power supply failure ! NO POSIX !
	BadSystemCall			= SIGSYS	// Bad system call ! NO POSIX !
};

/*enum struct SigAction
{

};*/

struct Signal final
{
	template <typename TFun>
	FORCEINLINE
	void
	static Listen(const Signum& sigcode, TFun&& fun) noexcept;
	template <typename TFun>
	FORCEINLINE
	void
	static Listen(Signum&& sigcode, TFun&& fun) noexcept;

	FORCEINLINE
	void
	static Send(const Signum& sigcode, uint32 pid) noexcept;
	FORCEINLINE
	void
	static Send(Signum&& sigcode, uint32 pid) noexcept;

	FORCEINLINE
	void
	static Self(const Signum& sigcode) noexcept;
	FORCEINLINE
	void
	static Self(Signum&& sigcode) noexcept;

	FORCEINLINE
	void
	static SelfGroup(const Signum& sigcode) noexcept;
	FORCEINLINE
	void
	static SelfGroup(Signum&& sigcode) noexcept;

	FORCEINLINE
	void
	static SendToThisProcessGroup(const Signum& sigcode) noexcept;
	FORCEINLINE
	void
	static SendToThisProcessGroup(Signum&& sigcode) noexcept;

	FORCEINLINE
	void
	static SendToAllAuthorizedProccesses(const Signum& sigcode) noexcept;
	FORCEINLINE
	void
	static SendToAllAuthorizedProccesses(Signum&& sigcode) noexcept;


	FORCEINLINE
	void
	static SendToTheGroupOf(const Signum& sigcode, uint gpid) noexcept;
	FORCEINLINE
	void
	static SendToTheGroupOf(Signum&& sigcode, uint gpid) noexcept;

	static const uint32	ThisPID;
	static const uint32	ThisGPID;
};

# include "template/Signal.inl"
#endif
