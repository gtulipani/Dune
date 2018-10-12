#ifndef __SOCKET_H__
#define __SOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SOCKET_CONNECTION_CLOSED -2
#define SOCKET_CONNECTION_ERROR -1
#define SOCKET_CONNECTION_SUCCESS 0

typedef struct socket_t {
	int fd;
} socket_t;

/**
 * Function that connects to a given {@param host} and {@param port} and creates
 * the socket_t instance in  {@param self}
 * @return SOCKET_CONNECTION_SUCCESS or SOCKET_CONNECTION_ERROR
 */
int socket_connect(socket_t *self, const char *host, const char *port);

/**
 * Function that opens a socket in the given {@param port} and configures a server
 * creating a socket_t instance in {@param self}
 * @return SOCKET_CONNECTION_SUCCESS or SOCKET_CONNECTION_ERROR
 */
int socket_bind_and_address(socket_t *self, const char *port);

/**
 * Function that waits for incoming connection in the port already configured in
 * {@param self} and returns the peer skt in {@param remote_skt}
 * @return SOCKET_CONNECTION_SUCCESS or SOCKET_CONNECTION_ERROR
 */
int socket_accept(socket_t *self, socket_t *remote_skt);

/**
 * Function that sends the message stored in {@param buffer} of size {@param size}
 * through the socket configured in {@param self}
 * @return the quantity of bytes sent or SOCKET_CONNECTION_ERROR
 */
long socket_send(socket_t *self, const char *buffer, long size);

/**
 * Function that receives a message and stores it in {@param buffer} of size {@param chunk_size}
 * through the socket configured in {@param self}
 * @return the quantity of bytes received or SOCKET_CONNECTION_ERROR
 */
long socket_recv(socket_t *self, char *buffer, long chunk_size);

/**
 * Function that sends an integer through the socket. Applies also special transformation
 * to be complient with the network endianess
 * @return SOCKET_CONNECTION_SUCCESS or SOCKET_CONNECTION_ERROR
 */
long socket_send_int(socket_t *self, int num);

/**
 * Function that receives an integer through the socket. Applies also special transformation
 * to be complient with the network endianess and puts the out in {@param out}
 * @return the quantity of bytes received or SOCKET_CONNECTION_ERROR
 */
int socket_recv_int(socket_t *self, int *out);

/**
 * Function that closes the socket entirely and releases the resource
 */
void socket_close(socket_t *self);

/**
 * Function that shutdowns the channel specified by {@param mode} in the {@oaram self}
 * @return SOCKET_CONNECTION_SUCCESS or SOCKET_CONNECTION_ERROR
 */
int socket_shutdown(socket_t *self, int mode);

#ifdef __cplusplus
}
#endif

#endif //__SOCKET_H__
