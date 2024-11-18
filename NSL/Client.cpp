#include "env/nsl.h"

// client
int	main(void)
{
	Socket	s;
	try
	{
		s.Connect("127.0.0.1", 8081);
		int		reception;
		float	gravity;
		s.Receive(&reception, &gravity);

		String	str;
		str.Reserve(9);
		s.Receive(Pair(&str[0], 8L));
		str[8] = 0;
		std::cout << reception << std::endl;
		std::cout << gravity << std::endl;
		std::cout << str << std::endl;
		s.Close();
	}
	catch (...)
	{
		std::cout << strerror(errno);
	}
	return (0);
}
