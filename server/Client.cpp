#include "Client.h"

#include <iostream>
#include "SOException.h"

Client::Client(Socket _socket) : socket(std::move(_socket)) {
    is_on = true;
}

#define INT32_SIZE 4

void Client::run() {
    int32_t msg_len;
    std::string msg;
    while (is_on) {
        try {
            msg_len = socket.receiveInt32();
            socket.receiveStr(msg, msg_len);
            std::cout << msg << std::endl;
            socket.sendInt32(2);
            socket.sendStr("OK");
        } catch (const SOException& e) {
            is_on = false;
        }
    }
}

bool Client::hasFinished() const {
    return !is_on;
}

void Client::stop() {
    is_on = false;
    socket.shutDown();
}
