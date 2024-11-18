#include "env/nsl.h"

// server
int	main(void)
{
	Socket	s;
	try
	{
		s.Bind("127.0.0.1", 8081);
		s.BecomeAListener();
		Socket::Info i = s.Accept();
		s.Send(4242, 9.18f, "BONJOUR\n");
		s.CloseConnection();
		s.Close();
	}
	catch (...)
	{
		std::cout << strerror(errno);
	}
	return (0);
}
