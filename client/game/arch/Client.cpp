#include "Client.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/EventHandler.h>

void Client::waitForEvent(std::string message) {
    bool received = false;
    while (!received) {
        NotificationEvent event = EventHandler::receiveNotificationEvent(socket);
        received = (event.message == message);
    }
}

Matrix Client::receiveTerrainMatrix() {
    return EventHandler::receiveMapConfigurationEvent(socket).matrix;
}

Client::Client(string host, string port) :
        host(move(host)),
        port(move(port)),
        game_status_events(game_status_mutex),
        output_messages(output_messages_mutex),
        events_looper_thread(game_status_events, output_messages),
        events_receptor_thread(socket, game_status_events),
        events_sender_thread(socket, output_messages) {}

void Client::start() {
    std::cout << "Starting game" << std::endl;
    try {
        socket = Socket(host, port);
        socket.connect();

        waitForEvent(CONNECTION_SUCCESS_EVENT);
        waitForEvent(GAME_STARTED_EVENT);
        waitForEvent(MAP_CONFIGURATION_EVENT);
        events_looper_thread.configure(receiveTerrainMatrix());

        events_looper_thread.start();
        events_receptor_thread.start();
        events_sender_thread.start();
        events_looper_thread.join();
        events_receptor_thread.join();
        events_sender_thread.join();
        socket.shutDown();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
