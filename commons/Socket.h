#ifndef __COMMONS_SOCKET_H__
#define __COMMONS_SOCKET_H__

#include <string>
#include <sys/types.h>

class Socket {
private:
    int fd;
    struct addrinfo * addrInfo;
    struct addrinfo * iterator;

    explicit Socket(int fd);

    void start();

    void sendBuff(const char* buff, unsigned int size) const;

    unsigned int receiveBuff(char* buff, unsigned int size) const;
public:
    Socket();

    Socket(const std::string& host, const std::string& port);

    Socket(Socket&& other);

    Socket& operator=(Socket&& other);
    
    bool valid() const;

    void connect();

    void bindAndListen(unsigned int qsize);

    Socket acceptClient() const;

    void sendInt32(int32_t n) const;

    int32_t receiveInt32() const;

    void sendStr(const std::string& str) const;

    unsigned int receiveStr(std::string& str, unsigned int size) const;

    /*
     * Sends two messages through the socket:
     * 1) Int32 containing the quantity of bytes to be received
     * 2) The message itself
     */
    unsigned int receiveWithSize(std::string& str) const;

    /*
     * Sends two messages through the socket:
     * 1) Int32 containing the quantity of bytes from the message
     * 2) The message itself
     */
    void sendWithSize(const std::string& str) const;

    void shutDown();

    ~Socket();

    Socket& operator=(const Socket& other) = delete;
    Socket(Socket& other) = delete;
};

#endif // __COMMONS_SOCKET_H__
