#include "Client.h"

#include <iostream>
#include "../../commons/SOException.h"

Client::Client(Socket _socket, shaque<std::string>& _sharedQueue)
: socket(std::move(_socket)), sharedQueue(_sharedQueue) {}

void Client::run() {
    std::cout << "Client connected" << std::endl;
    int32_t n, msg_len;
    std::string msg;
    while (this->isRunning()) {
        try {
            msg_len = socket.receiveInt32();
            n = socket.receiveStr(msg, msg_len);
            if (n == msg_len) {
                handleMsgSuccess(msg);
            } else {
                handleMsgError();
            }
        } catch (const SOException& e) {
            this->stop();
        }
    }
}

void Client::handleMsgError() {
    this->send("ERROR");
    this->stop();
}

void Client::handleMsgSuccess(const std::string& msg) {
    sharedQueue.push(msg);
}

void Client::send(const std::string& msg) const {
    socket.sendInt32(msg.length());
    socket.sendStr(msg);
}

void Client::terminate() {
    socket.shutDown();
}
