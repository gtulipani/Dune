#ifndef __COMMONS_SOCKET_H__
#define __COMMONS_SOCKET_H__

#include <string>
#include <iostream>

#include "socket_t.h"

class Socket {
private:
	bool initialized;
	socket_t skt;

	socket_t *getSkt();

public:
	Socket();

	// Disabling the constructor by copy because it's a socket
	Socket(const Socket &other) = delete;

	Socket(Socket &&other) noexcept;

	void connect(std::string host, std::string port);

	void bind(std::string port);

	Socket accept();

	void send(std::string source, unsigned long size);

	void send_int(int num);

	long receive(std::string &out, unsigned long size);

	int receive_int();

	void close();

	~Socket();

	// Disabling the assignment by copy because it's a socket
	Socket &operator=(const Socket &other) = delete;

	// Overloading the assignment by movement
	Socket &operator=(Socket &&other) noexcept;
};


#endif //__COMMONS_SOCKET_H__
