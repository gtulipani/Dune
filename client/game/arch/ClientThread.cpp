#include "ClientThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json/json.hpp>
#include <events/NotificationEvent.h>
#include <Matrix.h>
#include <TileUtils.h>
#include <events/EventHandler.h>

// Client Libraries
#include "ClientThread.h"
#include "../sdl/SdlTexture.h"
#include "../sdl/SdlWindow.h"

using nlohmann::json;

ClientThread::ClientThread(string host, string port) :
        host(move(host)),
        port(move(port)),
        game_status_events(game_status_mutex),
        output_messages(output_messages_mutex),
        game_thread(game_status_events, output_messages) {
}

void ClientThread::waitForEvent(std::string message) {
    bool received = false;
    while (!received) {
        NotificationEvent event = EventHandler::receiveNotificationEvent(socket);
        received = (event.message == message);
    }
}

Matrix ClientThread::receiveTerrainMatrix() {
    return EventHandler::receiveMapConfigurationEvent(socket).matrix;
}

void ClientThread::fetchServerEvents() {
    NotificationEvent notification_event = EventHandler::receiveNotificationEvent(socket);
    if (notification_event.message == GAME_STATUS_EVENT) {
        GameStatusEvent event = EventHandler::receiveGameStatusEvent(socket);
        game_status_events.push(event);
    }
}

void ClientThread::sendClientEvents() {
    std::list<ClientEvent> events = output_messages.popAll();
    std::for_each(events.begin(), events.end(), [this](ClientEvent &event) {
        EventHandler::sendEvent(socket, event);
    });
}

void ClientThread::processEvents() {
    while (game_thread.isRunning()) {
        fetchServerEvents();
        sendClientEvents();
    }
}

void ClientThread::run() {
    std::cout << "Starting game" << std::endl;
    try {
        game_thread.start();
        processEvents();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void ClientThread::terminate() {
    game_thread.stop();
    this->stop();
}

void ClientThread::connect() {
    socket = Socket(host, port);
    socket.connect();

    waitForEvent(CONNECTION_SUCCESS_EVENT);
}

void ClientThread::configure() {
    waitForEvent(GAME_STARTED_EVENT);
    waitForEvent(MAP_CONFIGURATION_EVENT);
    // Configure game with the matrix
    game_thread.configure(receiveTerrainMatrix());
}
