#include "EventsSenderThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/EventHandler.h>
#include <SOException.h>

EventsSenderThread::EventsSenderThread(Socket& socket, BlockingQueue<ClientEvent> &output_messages) :
    socket(socket),
    output_messages(output_messages) {}

void EventsSenderThread::run() {
    try {
        while (this->isRunning()) {
            std::list<ClientEvent> events = output_messages.popAll();
            std::for_each(events.begin(), events.end(), [this](ClientEvent &event) {
                EventHandler::sendEvent(socket, event);
            });
        }
    } catch (SOException &e) {
    } catch (std::exception& e) {
        std::cout << "Exception in EventsSenderThread: " << e.what() << std::endl;
    }
}

// Interrupts the execution by inserting an event inside the BlockingQueue
void EventsSenderThread::terminate() {
    output_messages.push(ClientEvent(0, 0, {0}, Point(0,0), Point(0,0)));
}
