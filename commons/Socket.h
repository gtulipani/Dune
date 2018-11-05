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

    void sendBuff(const char* buff, unsigned int size) const;

    unsigned int receiveBuff(char* buff, unsigned int size) const;

    void shutDown();

    ~Socket();

    Socket& operator=(const Socket& other) = delete;
    Socket(Socket& other) = delete;
};

#endif // __COMMONS_SOCKET_H__
