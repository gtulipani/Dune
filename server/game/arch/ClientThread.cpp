#include "ClientThread.h"

#include <iostream>
#include <SOException.h>
#include <events/EventHandler.h>

ClientThread::ClientThread(Socket _socket, shaque<ClientEvent>& _sharedQueue)
: socket(std::move(_socket)), sharedQueue(_sharedQueue) {}

void ClientThread::run() {
    std::cout << "Client connected" << std::endl;
    while (this->isRunning()) {
        try {
            ClientEvent event = EventHandler::receiveEvent(socket);
            sharedQueue.push(event);
        } catch (const SOException& e) {
            this->stop();
        }
    }
}

void ClientThread::handleMsgError() {
    this->send("ERROR");
    this->stop();
}

void ClientThread::send(const std::string& msg) const {
    socket.sendInt32(msg.length());
    socket.sendStr(msg);
}

void ClientThread::send(const GameConfigurationEvent& event) const {
    EventHandler::sendEvent(socket, event);
}

void ClientThread::send(const GameStatusEvent& event) const {
    EventHandler::sendEvent(socket, event);
}

void ClientThread::send(const NotificationEvent& event) const {
    EventHandler::sendEvent(socket, event);
}

void ClientThread::terminate() {
    socket.shutDown();
}
