#include "egide/egide.h"

	// THREADING EXEMPLE

float	ThreadTesting(String parameter /* can put infinite parameters */)
{
	bool	check;

	/* ... */
	parameter.Erase(2);
	//std::cout << "parameter: " << parameter << std::endl;
	Channel::Send("randomized", parameter);
	/* ... */
	check = Channel::Receive<bool>("goodSendingOK?");
	//std::cout << "check: " << check << std::endl;
	/* ... */
	//Thread::Return(42.42f);
	return (42.42f);
}

int	main(void)
{
	//IO::Echo << IO::SaveMode << "Retest\n";
	//IO::Echo << IO::Flush;

	//let	ez = 3;
	//std::cout << ez.ConstCast() << "\n";

	//std::cout << fonctionTest.Call<int>(21.312f) << std::endl;
	//letf	ft = EzF;
	//ft(2);

	/*let ez		= "EZEZEZ";
	let entier	= 3;
	std::cout << ez.ConstCast<const char*>() << std::endl; //EZEZEZ
	entier.Cast<int>() += 39;
	std::cout << entier.ConstCast<int>() << std::endl; //42*/


	/*ThreadQueue	quoicoubeh;
	quoicoubeh.Push(FonctionAWTF, 32.32f);
	quoicoubeh.WaitQueue();
	std::cout << "Push 1 finished\n";
	quoicoubeh.Push(FonctionAWTF, 32.32f);
	quoicoubeh.WaitQueue();
	std::cout << "Push 2 finished\n";
	quoicoubeh.Push(FonctionAWTF, 32.32f);
	quoicoubeh.WaitQueue();
	std::cout << "Push 3 finished\n";
	quoicoubeh.Push(FonctionAWTF, 32.32f);
	quoicoubeh.WaitQueue();
	std::cout << "Push 4 finished\n";*/

	//Mutex	m;
	//String	str("Jean");
	//Thread t(TestPtr, 2, 3);
	//t.Wait();

	//MultiThreading::Create("test1", ThreadTesting, String("norage"));
	//std::cout << "MT IsAlive ? " << (MultiThreading::IsAlive("test1") ? "yes" : "no") << std::endl;
	//std::cout << "MT IsExist ? " << (MultiThreading::IsExist("test1") ? "yes" : "no") << std::endl;
	//String a = Channel::Receive<String>("randomized");
	//Channel::Send("goodSendingOK?", true);
	//MultiThreading::Wait("test1");
	//std::cout << "MT IsAlive ? " << (MultiThreading::IsAlive("test1") ? "yes" : "no") << std::endl;
	//std::cout << "MT IsExist ? " << (MultiThreading::IsExist("test1") ? "yes" : "no") << std::endl;

	// std::cout << "\n\n------------------\n\n";

	//Thread	myThread(ThreadTesting, String("Bonjour, je suis Jean Guy ;) !!!"));
	//String	checkIfAllGood = Channel::Receive<String>("randomized");
	//std::cout << "Received !\n";
	//if (checkIfAllGood.Data() != nullptr)
	//	Channel::Send("goodSendingOK?", true);
	//else
	//	Channel::Send("goodSendingOK?", false);
	//std::cout << "Thread is alive ? " << (myThread.IsAlive() ? "yes" : "no") << std::endl;
	//float retValue = myThread.Get<float>();
	//std::cout << "retValue: " << retValue << std::endl;
	//std::cout << "Thread is alive ? " << (myThread.IsAlive() ? "yes" : "no") << std::endl;/**/
	//myThread.Wait();
	return (0);
}
