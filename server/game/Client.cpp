#include "Client.h"

#include <iostream>
#include "SOException.h"

Client::Client(Socket _socket, shaque<std::string> _sharedQueue)
: socket(std::move(_socket)), sharedQueue(_sharedQueue) {
    is_on = false;
}

#define INT32_SIZE 4

void Client::run() {
    int32_t msg_len;
    int32_t n;
    std::string msg;
    is_on = true;
    while (is_on) {
        try {
            msg_len = socket.receiveInt32();
            n = socket.receiveStr(msg, msg_len);
            if (n == msg_len) {
                handleMsgSuccess(msg);
            } else {
                handleMsgError();
            }
        } catch (const SOException& e) {
            is_on = false;
        }
    }
}

void Client::handleMsgError() {
    socket.sendInt32(5);
    socket.sendStr("ERROR");
}

void Client::handleMsgSuccess(std::string msg) {
    //sharedQueue.push(msg);
    std::cout << msg << std::endl;
    socket.sendInt32(2);
    socket.sendStr("OK");
}

bool Client::hasFinished() const {
    return !is_on;
}

void Client::stop() {
    is_on = false;
    socket.shutDown();
}
