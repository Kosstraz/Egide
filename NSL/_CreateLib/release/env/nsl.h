/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NEW_STANDARD_LIBRARY_H
#define NEW_STANDARD_LIBRARY_H

# include "NSLplatform.h"
# include "NSLSIMDplatform.h"

// !Two memory leaks in threading edge case (in the Thread class)
// !If not, no memory leak currently detected

/*
	MEMORY
*/

# include "NSLsrcs/Allocator.hpp"

/*
	TYPES CAPABILITIES
*/

# include "NSLsrcs/TypesCap.hpp"
# include "NSLsrcs/TypesName.hpp"
# include "NSLsrcs/IsSubclassOf.hpp"
# include "NSLsrcs/IsConvertible.hpp"

/*
	MATHS
*/

# include "NSLsrcs/Maths.hpp"
# include "NSLsrcs/CompilationMaths.hpp"
# include "NSLsrcs/MathVectors.h"

/*
	UTILITY
*/

# include "NSLsrcs/Meta.hpp"
# include "NSLsrcs/SmartPtr.hpp"
# include "NSLsrcs/Function.hpp"
// Todo:
# include "NSLsrcs/String.hpp"

/*
	UTILITY CONTAINER
*/

# include "NSLsrcs/Pair.hpp"
# include "NSLsrcs/Trio.hpp"
# include "NSLsrcs/Package.hpp"
# include "NSLsrcs/Unpack.hpp"

/*
Todo: Mutex::Fast			--> spinlock
Todo: SmartMutex			--> An abstract class for simply usage of mutex
Todo: Atomic class			--> Opérations atomiques
Todo: ThreadQueue			--> Gérer une file d'attente pour un thread
Todo: ThreadStealingQueue	--> Comme ThreadQueue, mais si un Thread n'a pas de file, il vole les actions en attente, des autres
Todo: ThreadProfiler		--> Profile la performance des threads
	THREADS
*/

# include "NSLsrcs/Sleep.hpp"
# include "NSLsrcs/Thread.hpp"
# include "NSLsrcs/Channel.hpp"
# include "NSLsrcs/Barrier.hpp"
# include "NSLsrcs/Async.hpp"
# include "NSLsrcs/Mutex.hpp"
# include "NSLsrcs/MultiThreading.hpp"

/*
	DEPRECATED
*/

# include "NSLsrcs/Pool.hpp"
# include "NSLsrcs/IOStreams.hpp"



/******************************
	EASY VOID DOCUMENTATION
******************************/

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Is not a real namespace, dot not use it for coding
//
// Is an easy "void" documentation
// Every text with a _ at the beginning and at the ending, and in full lowercase is a category
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
namespace NSL
{
	namespace _memory_
	{
		// Difference between HotReserve/HotFree & Reserve/Free is minimal
		// Check execution time and see if there is a big change
		class	Allocator;
	}

	namespace _maths_
	{
		// Class vector3f(loat) is a powerful mathematical structure
		class	Vector3f;
		// Class vector3d(ouble) is a powerful mathematical structure
		class	Vector3d;
	}

	namespace _utility_
	{
		// A smart pointer
		class	SmartPtr;
		// To store a function with any many arguments (or without)
		class	Function;
		// A String class
		class	String;
	}

	namespace _utility_containers_
	{
		// A structure containing 2 elements
		struct	Pair;
		// A structure containing 3 elements
		struct	Trio;
		// Package class encapsulates any many args
		struct	Package;
		// Put a function 'fun' and a Package<...> of many any args, and the Unpack class will depack your args in Package<...> and put them in the function 'fun'
		struct	Unpack;
		// NSUnpack, unlike Unpack, handles pointer to a non-static member method.
		struct	NSUnpack;
	}

	namespace _threads_
	{
		// A well threading system
		class	Thread;
		// --> Thread::Async <--
		//
		// Allows to a thread to pause, and another to continue him
		class	Async;
		// It's a simpler way to create thread and manage them.
		class	MultiThreading;
		// You can safely send & receive data between any threads
		class	Channel;
		// Create a barrier with a number, representing the number of threads that must wait for the barrier.
		// This allows you to synchronize threads so that they wait for each other.
		class	Barrier;
		// It's a simpler way to create Barrier and manage them.
		class	ManagedBarrier;
		// Allows you to protect your data in differents threads when you read or write them.
		class	Mutex;
		// --> Mutex::Strict <--
		//
		// Like the Mutex class, but here you can choose between ReadOnly locking or/and WriteRead locking.
		class	Strict;
	}

	// For mathematical calculations
	namespace	_maths_::Maths			{}
	// Allows heavy mathematical calculations to be performed during compilation
	namespace	_maths_::CMaths			{}
	// Capabilities of types
	namespace	_utility_::Types		{}
	// Metaprogramation
	namespace	_utility_::Meta			{}
	// Sleeping action
	namespace	_utility_::Sleep		{}
	// Actions in others threads
	namespace	_threads_::OtherThread	{}
	// Actions in this thread
	namespace	_threads_::ThisThread	{}
}


#endif
