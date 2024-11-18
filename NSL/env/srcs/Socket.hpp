#ifndef NSL_SOCKET_HPP
#define NSL_SOCKET_HPP

# include "Package.hpp"
# include "Unpack.hpp"
# include "String.hpp"
# include "Pair.hpp"
# include <unistd.h>
# include <poll.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ether.h>
# include <netinet/tcp.h>
# include <netinet/in_systm.h>
# include <arpa/inet.h>

enum struct SocketAddressFamily
{
	Unknow		= -1,				// The SocketAddressFamily is unknow
	Default		= AF_INET,			// Equivalent to IPv4
	IPv4 		= AF_INET,
	IPv6 		= AF_INET6,
	Linked		= AF_PACKET,		// Low-level/physicaly linked communication (like Ethernet)
	Netlink		= AF_NETLINK,		// Communication between the UNIX kernel and the user's space
# if defined(AF_LOCAL)
	LocalHost	= AF_LOCAL,			// Communication only with the localhost
# elif defined(AF_UNIX)
	LocalHost	= AF_UNIX,			// Communication only with the localhost
# endif
# if defined(AF_BLUETOOTH)
	Bluetooth	= AF_BLUETOOTH,
# endif
# if defined(AF_IRDA)
	Infrared	= AF_IRDA,			// Infrared Data Association
# endif
# if defined(AF_ROSE)
	ROSE		= AF_ROSE,			// For ham radio communication
# endif
# if defined(AF_AX25)
	AX25		= AF_AX25,			// For ham radio communication
# endif
# if defined(AF_X25)
	X25			= AF_X25,			// ! Now deprecated !
# endif
# if defined(AF_IPX)
	IPX			= AF_IPX,			// ! Now deprecated !
# endif
# if defined(AF_DECnet)
	DECnet		= AF_DECnet,		// ! Now deprecated !
# endif
# if defined(AF_APPLETALK)
	AppleTalk	= AF_APPLETALK		// ! Now deprecated !
# endif
};

enum struct SocketType
{
	Unknow		= -1,				// The SocketType is unknow
	TCP			= SOCK_STREAM,		// Provides a reliable, connection-oriented data flow, guarantees data integrity (delivery in order, no duplicates)
	UDP			= SOCK_DGRAM,		// Provides an unreliable, connectionless datagram service, does not guarantee packet order or delivery, but is faster than SocketType::TCP
	RAW			= SOCK_RAW,			// Provides direct access to IP packets, without kernel processing, used for custom network protocol development and packet manipulation. Requires administrative privileges
	RDM			= SOCK_RDM,			// Ensures reliable delivery of datagrams, but does not ensure the connection
# if defined(SOCK_PACKET)
	Linked		= SOCK_PACKET,		// Used to receive packets at data link level, like AF_PACKET in Linux, !deprecated on many modern system!
# endif
	Sequential	= SOCK_SEQPACKET	// Similar to SocketType::UDP but guarantees the integrity and sequence of packets.
};

enum struct SocketProtocol
{
	Unknow	= -1,			// The SocketProtocol is unknow
	Auto	= 0,
	TCP		= IPPROTO_TCP,
	UDP		= IPPROTO_UDP,
	ICMP	= IPPROTO_ICMP, // Used for control protocols, such as ping
	IPv4	= IPPROTO_IP,
	IPv6	= IPPROTO_IPV6
};

/*struct SocketOLevel
{
	enum
	{
		ReUseAddr	= SO_REUSEADDR,	// Allows a local address to be reused after it has been closed. Very useful for restarting a server without delay
		ReUsePort	= SO_REUSEPORT,	// Allows several sockets to share the same local port (often only supported under Linux)
		Broadcast	= SO_BROADCAST,	// Allows broadcast packets (UDP) for the socket
		KeepAlive	= SO_KEEPALIVE,	// Keeps connections active by periodically sending messages to ensure that the connection is intact (useful for TCP)
		Linger		= SO_LINGER,	// Controls when the socket is closed and how long it waits to clear the pending data
		RCVBuf		= SO_RCVBUF,	//
	};
};*/

typedef ushort	ushort_port;
typedef uint32	uint32_family;

// ! Only INET and INET6 are supported NOW !
//
// Todo: setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
// Todo: getprotobyname(const char *name)
// Todo: gethostbyname(const char *name)
// Todo: getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
// Todo: freeaddrinfo(struct addrinfo *res)
// Todo: ...
class Socket
{
public:
	struct Location
	{
		ushort	family;
		ushort	port;
		uint32	address;
		uchar	 __private_padding__[
											sizeof(struct sockaddr)
										-	sizeof(ushort_port)
										-	sizeof(uint32_family)
										-	__SOCKADDR_COMMON_SIZE
									];
	};

	struct Core
	{
		Location	loc;
		uint32		locLen = sizeof(struct sockaddr);
	};

	struct Info
	{
		Info()	= default;
		~Info()	= default;
		SocketAddressFamily	family;
		ushort				port;
		::String			address;
		int					socketID;
	};

public:
	// can be already bound ( 'bind()' )
	FORCEINLINE
	Socket(Socket&& s) noexcept;
	// not bound ( bind() )
	FORCEINLINE
	Socket(const Socket& s) noexcept;
	// not bound ( bind() )
	FORCEINLINE
	Socket(SocketAddressFamily&& af = SocketAddressFamily::IPv4, SocketType&& type = SocketType::TCP, SocketProtocol&& protocol = SocketProtocol::Auto) noexcept;
	// not bound ( bind() )
	FORCEINLINE
	Socket(const SocketAddressFamily& af, const SocketType& type, const SocketProtocol& protocol) noexcept;
	FORCEINLINE
	virtual ~Socket() noexcept;

	FORCEINLINE
	void
	CloseConnection() noexcept;

	FORCEINLINE
	void
	Close() noexcept;

	FORCEINLINE
	void
	Bind(String&& address, ushort port);

	FORCEINLINE
	void
	Bind(const String& address, ushort port);

	// @param address Can obviously be an IP
	FORCEINLINE
	void
	Connect(String&& address, ushort port);
	// @param address Can obviously be an IP
	FORCEINLINE
	void
	Connect(const String& address, ushort port);


	FORCEINLINE
	Socket::Info
	Accept();


	FORCEINLINE
	void
	BecomeAListener(int queueLen);
	FORCEINLINE
	void
	BecomeAListener();

	template <typename... TArgs>
	FORCEINLINE
	long
	Send(const TArgs&... arg) const noexcept;
	template <typename... TArgs>
	FORCEINLINE
	long
	Receive(TArgs*... buffer) const noexcept;


	template <typename... TArgs>
	FORCEINLINE
	long
	Send(Pair<const TArgs&, long>... arg) const noexcept;
	template <typename... TArgs>
	FORCEINLINE
	long
	Receive(Pair<TArgs*, long>... buffer) const noexcept;


	FORCEINLINE
	Socket::Info
	GetInfo() noexcept;

	FORCEINLINE
	const int&
	GetSocketDescriptor() const noexcept;
	FORCEINLINE
	const SocketAddressFamily&
	GetSocketAddressFamily() const noexcept;
	FORCEINLINE
	const SocketType&
	GetSocketType() const noexcept;
	FORCEINLINE
	const SocketProtocol&
	GetSocketProtocol() const noexcept;

protected:
	struct CanNotListen			: std::exception { virtual const char* what() const noexcept	{ return ("Socket can not listen");							} };
	struct AddressSizeTooLong	: std::exception { virtual const char* what() const noexcept	{ return ("Socket address size too long (max 14 bytes)");	} };
	struct CanNotConnect		: std::exception { virtual const char* what() const noexcept	{ return ("Socket can not connect");						} };
	struct CanNotAccept			: std::exception { virtual const char* what() const noexcept	{ return ("Socket can not accept");							} };
	struct BadSocketInfoFD		: std::exception { virtual const char* what() const noexcept	{ return ("Socket::Info maybe not have a valid .fd");		} };
	struct SocketHasBeenClosed	: std::exception { virtual const char* what() const noexcept	{ return ("Socket has been closed");						} };
	struct SocketAlreadyBound	: std::exception { virtual const char* what() const noexcept	{ return ("Socket is already bound");						} };
	struct SocketFailedBinding	: std::exception { virtual const char* what() const noexcept	{ return ("Socket failed her binding");						} };

protected:
	int							fd;
	int							fd_connected;
	bool						bound;
	Socket::Core				core;
	const SocketAddressFamily	af;
	const SocketType			type;
	const SocketProtocol		protocol;
};

# include "template/Socket.inl"
#endif
