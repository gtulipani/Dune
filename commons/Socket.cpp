#include <iostream>
#include <string>
#include <sys/socket.h>

#include "Socket.h"
#include "ConnectionRefusedException.h"
#include "ClientClosedSocketException.h"

socket_t *Socket::getSkt() {
	return &skt;
}

Socket::Socket() : initialized(false) {
}

Socket::Socket(Socket &&other) noexcept : Socket() {
	this->initialized = other.initialized;
	this->skt = other.skt;

	other.initialized = false;
}

void Socket::connect(std::string host, std::string port) {
	// Connect through the socket as a client
	if (socket_connect(&skt, host.c_str(), port.c_str()) ==
		SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}
	initialized = true;
}

void Socket::bind(std::string port) {
	// Connect through the socket as a server
	if (socket_bind_and_address(&skt, port.c_str()) ==
		SOCKET_CONNECTION_ERROR) {
		throw ConnectionRefusedException();
	}
	initialized = true;
}

Socket Socket::accept() {
	// Accept a connection through the socket
	Socket peer_socket{};
	if (!initialized || (socket_accept(&skt, peer_socket.getSkt()) ==
						 SOCKET_CONNECTION_ERROR)) {
		throw ConnectionRefusedException();
	}
	peer_socket.initialized = true;
	return peer_socket;
}

void Socket::send(std::string source, unsigned long size) {
	// Send message through the socket
	if (!initialized ||
		(socket_send(&skt, source.c_str(), size) == SOCKET_CONNECTION_ERROR)) {
		throw ConnectionRefusedException();
	}
}

void Socket::send_int(int num) {
	// Send int through the socket
	if (!initialized ||
		(socket_send_int(&skt, num) == SOCKET_CONNECTION_ERROR)) {
		throw ConnectionRefusedException();
	}
}

long Socket::receive(std::string &out, unsigned long size) {
	if (size == 0) {
		return 0;
	}
	if (!initialized) {
		throw ConnectionRefusedException();
	}
	// Receive message through the socket
	char *buffer = (char *) malloc(size);
	long bytes_received = socket_recv(&skt, buffer, size);
	if (bytes_received == SOCKET_CONNECTION_ERROR) {
		free(buffer);
		throw ConnectionRefusedException();
	}
	out = std::string(buffer, static_cast<unsigned long>(bytes_received));
	free(buffer);
	return bytes_received;
}

int Socket::receive_int() {
	int result;
	if (!initialized) {
		throw ConnectionRefusedException();
	}
	// Receive int through the socket
	switch (socket_recv_int(&skt, &result)) {
		case SOCKET_CONNECTION_ERROR: {
			throw ConnectionRefusedException();
		}
		case SOCKET_CONNECTION_CLOSED: {
			throw ClientClosedSocketException();
		}
		default: {
			return result;
		}
	}
}

void Socket::close() {
	if (initialized) {
		if (socket_shutdown(&skt, SHUT_RDWR) == SOCKET_CONNECTION_ERROR) {
			throw ConnectionRefusedException();
		}
		socket_close(&skt);
		initialized = false;
	}
}

Socket &Socket::operator=(Socket &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->initialized = other.initialized;
	this->skt = other.skt;

	other.initialized = false;

	return *this;
}

Socket::~Socket() {
	if (initialized) {
		socket_close(&skt);
	}
}
