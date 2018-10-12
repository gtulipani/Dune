#define _POSIX_C_SOURCE 200112L

#include "socket_t.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define PROTOCOL_INT_BYTES 4

/**
 * Static function that transforms a num to big endian (to be able to send through
 * the socket)
 */
static int to_big_endian(const int num) {
	return htonl((uint32_t) num);
}

/**
 * Static function that transforms a num from big endian to current architecture
 * (supposed to be received through socket)
 */
static int32_t from_big_endian(const char *buf) {
	return ntohl(*(int32_t *) buf);
}


int socket_connect(socket_t *self, const char *host, const char *port) {
	int s = 0;
	int val = 1;

	struct addrinfo hints;
	struct addrinfo *ptr;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)        */
	hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)       */
	hints.ai_flags = 0;              /* 0 for client */

	s = getaddrinfo(host, port, &hints, &ptr);

	if (s != 0) {
		return SOCKET_CONNECTION_ERROR;
	}

	int fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (fd == -1) {
		freeaddrinfo(ptr);
		return SOCKET_CONNECTION_ERROR;
	}

	s = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (s == -1) {
		close(fd);
		freeaddrinfo(ptr);
		return SOCKET_CONNECTION_ERROR;
	}

	int remote_skt = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
	if (remote_skt == -1) {
		close(fd);
		freeaddrinfo(ptr);
		return SOCKET_CONNECTION_ERROR;
	}

	freeaddrinfo(ptr);
	self->fd = fd;
	return SOCKET_CONNECTION_SUCCESS;
}

int socket_bind_and_address(socket_t *self, const char *port) {
	int s = 0;
	int val;

	struct addrinfo hints;
	struct addrinfo *ptr;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)   */
	hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)  */
	hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE for server         */

	s = getaddrinfo(NULL, port, &hints, &ptr);

	if (s != 0) {
		return SOCKET_CONNECTION_ERROR;
	}

	int fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (fd == -1) {
		freeaddrinfo(ptr);
		return SOCKET_CONNECTION_ERROR;
	}

	val = 1;
	s = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (s == -1) {
		close(fd);
		freeaddrinfo(ptr);
		return SOCKET_CONNECTION_ERROR;
	}

	s = bind(fd, ptr->ai_addr, ptr->ai_addrlen);
	if (s == -1) {
		close(fd);
		freeaddrinfo(ptr);
		return SOCKET_CONNECTION_ERROR;
	}

	freeaddrinfo(ptr);
	s = listen(fd, 20);
	if (s == -1) {
		close(fd);
		return SOCKET_CONNECTION_ERROR;
	}

	self->fd = fd;
	return SOCKET_CONNECTION_SUCCESS;
}

int socket_accept(socket_t *self, socket_t *remote_skt) {
	remote_skt->fd = accept(self->fd, NULL, NULL);
	return (remote_skt->fd == -1) ? SOCKET_CONNECTION_ERROR
								  : SOCKET_CONNECTION_SUCCESS;
}

long socket_send(socket_t *self, const char *buffer, long size) {
	long sent = 0;
	int s = 0;
	bool is_the_socket_valid = true;
	while (sent < size && is_the_socket_valid) {
		s = (int) send(self->fd, &buffer[sent], (size_t) (size - sent),
					   1);

		if (s <= 0) {
			is_the_socket_valid = false;
		} else {
			sent += s;
		}
	}

	if (is_the_socket_valid) {
		return sent;
	} else {
		return SOCKET_CONNECTION_ERROR;
	}
}

long socket_recv(socket_t *self, char *buffer,
				 long chunk_size) {
	long received = 0;
	int s = 0;
	bool are_we_connected = true;
	bool result = true;
	while (are_we_connected && (received < chunk_size)) {
		s = (int) recv(self->fd, &buffer[received],
					   (chunk_size - received),
					   1);

		if (s == 0) { // Socket closed
			are_we_connected = false;
		} else if (s < 0) { // Error
			are_we_connected = false;
			result = false;
		} else {
			received += s;
		}
	}
	return result ? received : SOCKET_CONNECTION_ERROR;
}

long socket_send_int(socket_t *self, int num) {
	int transformed_int = to_big_endian(num);
	char *buffer = (char *) (unsigned char *) &transformed_int;
	return socket_send(self, buffer, PROTOCOL_INT_BYTES);
}

int socket_recv_int(socket_t *self, int *out) {
	char buffer[PROTOCOL_INT_BYTES];
	switch (socket_recv(self, buffer, PROTOCOL_INT_BYTES)) {
		case SOCKET_CONNECTION_ERROR: {
			return SOCKET_CONNECTION_ERROR;
		}
		case 0: { // According to recv documentation, the socket has been closed
			return SOCKET_CONNECTION_CLOSED;
		}
		default: {
			*out = from_big_endian(buffer);
			return SOCKET_CONNECTION_SUCCESS;
		}
	}
}

void socket_close(socket_t *self) {
	close(self->fd);
}

int socket_shutdown(socket_t *self, int mode) {
	return (shutdown(self->fd, mode) == -1) ? SOCKET_CONNECTION_ERROR
											: SOCKET_CONNECTION_SUCCESS;
}
