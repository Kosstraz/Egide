/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NEW_STANDARD_LIBRARY_H
#define NEW_STANDARD_LIBRARY_H

# include "NSLplatform.h"
# include "NSLSIMDplatform.h"

//Todo General: 'Memory::MemCpy' with SIMD operations
//Todo General: Finish Queue<T>
//Todo General: Make a List class (a base class for all list type classes)
//Todo General: Make a Stack class
//Todo General: Make a BTree class

// !Two memory leaks in threading edge case (in the Thread class)
// !If not, no memory leak currently detected

/*
	MEMORY
*/

# include "NSLsrcs/Allocator.hpp"

/*
	NETWORK
*/

# include "NSLsrcs/Socket.hpp"

/*
	TYPES CAPABILITIES
*/

# include "NSLsrcs/TypesCap.hpp"

/*
	MATHS
*/

# include "NSLsrcs/Maths.hpp"
# include "NSLsrcs/CompilationMaths.hpp"
# include "NSLsrcs/MathVectors.h"

/*
	UTILITY
*/

# include "NSLsrcs/Signal.hpp"
# include "NSLsrcs/Iterator.hpp"
# include "NSLsrcs/Meta.hpp"
# include "NSLsrcs/SmartPtr.hpp"
# include "NSLsrcs/Function.hpp"
// Todo: little optimizations
# include "NSLsrcs/String.hpp"
//# include "srcs/VTable.hpp"

/*
	UTILITY CONTAINER
*/

# include "NSLsrcs/Let.hpp"
# include "NSLsrcs/Pair.hpp"
# include "NSLsrcs/Trio.hpp"
# include "NSLsrcs/Package.hpp"
# include "NSLsrcs/Unpack.hpp"

/*
	CONTAINERS
*/

# include "NSLsrcs/Queue.hpp"

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
# include "NSLsrcs/ThreadQueue.hpp"
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

	namespace _optimization_
	{
		// An "Empty Base Optimization" class
		class	EBO;
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
	}

	namespace _containers_
	{
		class	Queue;
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
		// --> Mutex::Recursive <--
		//
		// A Mutex to use in recursivity
		class	Recursive;
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
