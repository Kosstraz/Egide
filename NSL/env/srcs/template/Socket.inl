#include "Socket.hpp"

Socket::Socket(const Socket& socket) noexcept : fd_connected(-1), bound(false), af(socket.af), type(socket.type), protocol(socket.protocol)
{
	this->fd = dup(socket.fd);
	this->core = socket.core;
}

Socket::Socket(Socket&& socket) noexcept : fd_connected(Meta::Move(socket.fd_connected)), bound(Meta::Move(socket.bound)), af(Meta::Move(socket.af)), type(Meta::Move(socket.type)), protocol(Meta::Move(socket.protocol))
{
	this->fd = Meta::Move(socket.fd);
	this->core = Meta::Move(socket.core);
	socket.fd = -1;
	socket.core = Socket::Core();
}

Socket::Socket(SocketAddressFamily&& af, SocketType&& type, SocketProtocol&& protocol) noexcept : fd_connected(-1), bound(false), af(Meta::Move(af)), type(Meta::Move(type)), protocol(Meta::Move(protocol))
{
	this->fd = socket(static_cast<int>(this->af), static_cast<int>(this->type), static_cast<int>(this->protocol));
}

Socket::Socket(const SocketAddressFamily& af, const SocketType& type, const SocketProtocol& protocol) noexcept : fd_connected(-1), bound(false), af(af), type(type), protocol(protocol)
{
	this->fd = socket(static_cast<int>(af), static_cast<int>(type), static_cast<int>(protocol));
}

Socket::~Socket() noexcept
{
	this->CloseConnection();
	this->Close();
}

void
Socket::Close() noexcept
{
	if (this->fd != -1)
	{
		close(this->fd);
		this->fd = -1;
	}
}

void
Socket::CloseConnection() noexcept
{
	if (this->fd_connected != -1)
	{
		close(this->fd_connected);
		this->fd_connected = -1;
	}
}

void
Socket::Bind(String&& address, ushort port)
{
	if (this->bound) [[unlikely]]
		 throw (Socket::SocketAlreadyBound());
	inet_pton(static_cast<int>(this->af), address, &this->core.loc.address);
	this->core.loc.port = htons(port);
	this->core.loc.family = static_cast<int>(this->af);
	if (bind(this->fd, reinterpret_cast<const sockaddr*>(&this->core.loc), this->core.locLen) == -1) [[unlikely]]
		throw (Socket::SocketFailedBinding());
	this->bound = true;
}

void
Socket::Bind(const String& address, ushort port)
{
	if (this->bound) [[unlikely]]
		throw (Socket::SocketAlreadyBound());
	inet_pton(static_cast<int>(this->af), address, &this->core.loc.address);
	this->core.loc.port = htons(port);
	this->core.loc.family = static_cast<ushort>(this->af);
	if (bind(this->fd, reinterpret_cast<const sockaddr*>(&this->core.loc), this->core.locLen) == -1) [[unlikely]]
		throw (Socket::SocketFailedBinding());
	this->bound = true;
}








void
Socket::Connect(String&& address, ushort port)
{
	inet_pton(static_cast<int>(this->af), address, &this->core.loc.address);
	this->core.loc.port = htons(port);
	this->core.loc.family = static_cast<ushort>(this->af);
	if (connect(this->fd, reinterpret_cast<const sockaddr*>(&this->core.loc), this->core.locLen) == -1) [[unlikely]]
		throw (Socket::CanNotConnect());
}
void
Socket::Connect(const String& address, ushort port)
{
	inet_pton(static_cast<int>(this->af), address, &this->core.loc.address);
	this->core.loc.port = htons(port);
	this->core.loc.family = static_cast<ushort>(this->af);
	if (connect(this->fd, reinterpret_cast<const sockaddr*>(&this->core.loc), this->core.locLen) == -1) [[unlikely]]
		throw (Socket::CanNotConnect());
}







Socket::Info
Socket::Accept()
{
	Socket::Core	tmp;
	Socket::Info	ret;

	if ((ret.socketID = accept(this->fd, reinterpret_cast<struct sockaddr*>(&tmp.loc), &tmp.locLen)) == -1)
		throw (Socket::CanNotAccept());
	if (tmp.loc.family == static_cast<ushort>(SocketAddressFamily::IPv4))
	{
		char*	buffer;
		ret.address.Reserve(INET_ADDRSTRLEN);
		buffer = const_cast<char*>(&ret.address[0]);
		inet_ntop(tmp.loc.family, &tmp.loc.address, buffer, INET_ADDRSTRLEN);
	}
	else if (tmp.loc.family == static_cast<ushort>(SocketAddressFamily::IPv6))
	{
		char*	buffer;
		ret.address.Reserve(INET6_ADDRSTRLEN);
		buffer = const_cast<char*>(&ret.address[0]);
		inet_ntop(tmp.loc.family, &tmp.loc.address, buffer, INET6_ADDRSTRLEN);
	}
	ret.port = htons(this->core.loc.port);
	this->fd_connected = ret.socketID;
	return (ret);
}






void
Socket::BecomeAListener(int queueLen)
{
	if (this->fd == -1) [[unlikely]]
		throw (Socket::SocketHasBeenClosed());
	else if (queueLen > SOMAXCONN)
		queueLen = SOMAXCONN;
	if (listen(this->fd, queueLen) == -1) [[unlikely]]
		throw (Socket::CanNotListen());
}
void
Socket::BecomeAListener()
{
	if (this->fd == -1) [[unlikely]]
		throw (Socket::SocketHasBeenClosed());
	else if (listen(this->fd, SOMAXCONN) == -1) [[unlikely]]
		throw (Socket::CanNotListen());
}

template <typename... TArgs>
long
Socket::Send(const TArgs&... arg) const noexcept
{
	long	ret = 0L;
	ret += ((send(this->fd_connected, &arg, sizeof(arg), 0)), ...);
	return (ret);
}

template <typename... TArgs>
long
Socket::Receive(TArgs*... buffer) const noexcept
{
	long ret = 0L;
	ret += ((recv(this->fd, buffer, sizeof(TArgs), 0)), ...);
	return (ret);
}

template <typename... TArgs>
long
Socket::Send(Pair<const TArgs&, long>... arg) const noexcept
{
	long	ret = 0L;
	ret += ((send(this->fd_connected, &arg.a, arg.b, 0)), ...);
	return (ret);
}

template <typename... TArgs>
long
Socket::Receive(Pair<TArgs*, long>... buffer) const noexcept
{
	long ret = 0L;
	ret += ((recv(this->fd, buffer.a, buffer.b, 0)), ...);
	return (ret);
}


Socket::Info
Socket::GetInfo() noexcept
{
	//Socket::Info		ret;
	//sockaddr_storage	addr;
//
	//getsockname(this->fd, reinterpret_cast<sockaddr*>(&addr), &ret.len);
	//for (uchar i = 0U ; addr.__ss_padding[i] ; i++)
	//	ret.address[i] = addr.__ss_padding[i];
	//ret.address[ret.len] = '\0';
	//ret.family = addr.ss_family;
	//return (ret);
	return (Socket::Info());
}






const int&
Socket::GetSocketDescriptor() const noexcept
{
	return (this->fd);
}

const SocketAddressFamily&
Socket::GetSocketAddressFamily() const noexcept
{
	return (this->af);
}

const SocketType&
Socket::GetSocketType() const noexcept
{
	return (this->type);
}

const SocketProtocol&
Socket::GetSocketProtocol() const noexcept
{
	return (this->protocol);
}
