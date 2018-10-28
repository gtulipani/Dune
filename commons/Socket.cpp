#define _POSIX_C_SOURCE 200112L

#include "Socket.h"

#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include "SOException.h"

Socket::Socket() {
    this->addrInfo = nullptr;
    this->fd = -1;
    this->iterator = nullptr;
}

Socket::Socket(const char* host, const char* port) {
    struct addrinfo hints;
    ::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // Flag se ignora si host no es nullptr

    int s;
    s = ::getaddrinfo(host, port, &hints, &(this->addrInfo));
    if (s != 0) throw SOException(::gai_strerror(s));

    this->iterator = this->addrInfo;
    this->start();

    int val = 1;
    s = ::setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (s == -1) throw SOException();
}

Socket::Socket(int fd) {
    this->addrInfo = nullptr;
    this->iterator = nullptr;
    this->fd = fd;
}

Socket::Socket(Socket&& other) {
    this->iterator = other.iterator;
    this->addrInfo = other.addrInfo;
    this->fd = other.fd;

    other.iterator = nullptr;
    other.addrInfo = nullptr;
    other.fd = -1;
}

Socket& Socket::operator=(Socket&& other) {
    this->iterator = other.iterator;
    this->addrInfo = other.addrInfo;
    this->fd = other.fd;

    other.iterator = nullptr;
    other.addrInfo = nullptr;
    other.fd = -1;

    return *this;
}

void Socket::start() {
    bool success = false;
    while (this->iterator != nullptr && !success) {
        this->fd = ::socket(this->iterator->ai_family,
                     this->iterator->ai_socktype,
                     this->iterator->ai_protocol);
        if (this->fd == -1) {
            this->iterator = this->iterator->ai_next;
        } else {
            success = true;
        }
    }
    if (!success) throw SOException();
}

void Socket::connect() {
    int s;
    bool success;
    do {
        s = ::connect(this->fd,
                      this->iterator->ai_addr,
                      this->iterator->ai_addrlen);
        if (s == -1) {
            close(this->fd);
            this->iterator = this->iterator->ai_next;
            this->start();
        } else {
            success = true;
        }
    } while (this->iterator != nullptr && !success);

    if (!success) throw SOException();
}

void Socket::bindAndListen(unsigned int qsize) {
    int s = bind(this->fd, this->iterator->ai_addr, this->iterator->ai_addrlen);
    if (s == -1) throw SOException();

    s = listen(this->fd, qsize);
    if (s == -1) throw SOException();
}

Socket Socket::acceptClient() const {
    int fd = accept(this->fd, NULL, NULL);
    if (fd == -1) throw SOException();
    return Socket(fd);
}

#define INT32_SIZE 4

void Socket::sendInt32(int32_t n) const {
    n = htonl(n);
    sendBuff((char*)&n, INT32_SIZE);
}

int32_t Socket::receiveInt32() const {
    int32_t n;
    receiveBuff((char*)&n, INT32_SIZE);
    n = ntohl(n);
    return n;
}

void Socket::sendStr(const std::string& str) const {
    sendBuff(str.c_str(), str.length());
}

unsigned int Socket::receiveStr(std::string& str, unsigned int size) const {
    char* buff = new char[size + 1];
    unsigned int n = receiveBuff(buff, size);
    buff[n] = 0;
    str = buff;
    delete[] buff;
    return n;
}

void Socket::sendBuff(const char* buff, unsigned int size) const {
    size_t bytes_sent = 0;
    int s;

    while (bytes_sent < size) {
        s = send(this->fd, buff + bytes_sent, size - bytes_sent, MSG_NOSIGNAL);
        if (s == -1) {
            throw SOException();
        } else if (s == 0) {
            throw SOException("Broken pipe error");
        } else {
            bytes_sent += s;
        }
    }
}

unsigned int Socket::receiveBuff(char* buff, unsigned int size) const {
    memset(buff, 0, size);
    int s;
    size_t bytes_recived = 0;

    while (bytes_recived < size) {
        s = recv(this->fd, buff + bytes_recived, size - bytes_recived, 0);
        if (s == -1) {
            throw SOException();
        } else if (s == 0) {
            throw SOException("Broken pipe error");
        } else {
            bytes_recived += s;
        }
    }

    return bytes_recived;
}

void Socket::shutDown() {
    shutdown(this->fd, SHUT_RDWR);
}

Socket::~Socket() {
    if (this->addrInfo) freeaddrinfo(this->addrInfo);
    if (this->fd != -1) close(this->fd);
}
