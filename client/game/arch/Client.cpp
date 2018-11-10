#include "Client.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json/json.hpp>
#include <events/NotificationEvent.h>
#include <Matrix.h>
#include <TileUtils.h>
#include <events/EventHandler.h>

// Client Libraries
#include "Client.h"
#include "../sdl/SdlTexture.h"
#include "../sdl/SdlWindow.h"

using nlohmann::json;

void Client::waitForEvent(std::string message) {
    bool received = false;
    while (!received) {
        NotificationEvent event = EventHandler::receiveNotificationEvent(socket);
        received = (event.message == message);
    }
}

Client::Client(string host, string port) : host(move(host)), port(move(port)) {}

void Client::connect() {
    socket = Socket(host, port);
    socket.connect();

    waitForEvent(CONNECTION_SUCCESS_EVENT);
}

void Client::configure() {
    waitForEvent(GAME_STARTED_EVENT);
    waitForEvent(MAP_CONFIGURATION_EVENT);
    // Load Matrix
    game.configure(std::move(socket));
}

void Client::startGame() {
    try {
        game.start();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
