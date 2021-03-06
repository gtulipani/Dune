#include "Client.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/EventHandler.h>

void Client::waitForEvent(int message) {
    bool received = false;
    while (!received) {
        NotificationEvent event = EventHandler::receiveNotificationEvent(socket);
        received = (event.message == message);
    }
}

GameConfigurationEvent Client::receiveGameConfiguration() {
    return EventHandler::receiveGameConfigurationEvent(socket);
}

Client::Client(string host, string port) :
        host(move(host)),
        port(move(port)),
        game_ended(false),
        game_status_events(game_status_mutex),
        output_messages(output_messages_mutex),
        events_looper_thread(game_status_events, output_messages, game_ended),
        events_receptor_thread(socket, game_status_events, game_ended),
        events_sender_thread(socket, output_messages) {}

void Client::start() {
    try {
        socket = Socket(host, port);
        socket.connect();

        waitForEvent(CONNECTION_SUCCESS_EVENT);
        waitForEvent(GAME_STARTED_EVENT);
        waitForEvent(GAME_CONFIGURATION_EVENT);
        GameConfigurationEvent event = receiveGameConfiguration();
        events_looper_thread.configure(event.player_id, event.matrix);

        events_looper_thread.start();
        events_receptor_thread.start();
        events_sender_thread.start();

        // Wait for events_looper_thread to join
        events_looper_thread.join();

        // Force events_receptor_thread to join by closing the socket
        socket.shutDown();
        events_receptor_thread.join();

        // Force events_sender_thread to stop because it uses a BlockingQueue
        events_sender_thread.stop();
        events_sender_thread.join();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
