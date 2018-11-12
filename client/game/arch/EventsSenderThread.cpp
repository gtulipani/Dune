#include "EventsSenderThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/EventHandler.h>

EventsSenderThread::EventsSenderThread(Socket& socket, shaque<ClientEvent> &output_messages) :
    socket(socket),
    output_messages(output_messages) {}

void EventsSenderThread::run() {
    std::cout << "Starting EventsSenderThread" << std::endl;
    try {
        while (this->isRunning()) {
            std::list<ClientEvent> events = output_messages.popAll();
            std::for_each(events.begin(), events.end(), [this](ClientEvent &event) {
                EventHandler::sendEvent(socket, event);
            });
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void EventsSenderThread::terminate() {
    this->stop();
}
