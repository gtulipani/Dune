#include <iostream>
#include "EventHandler.h"

// Commons Libraries
#include "../Socket.h"
#include "../json/json.hpp"
#include "../json/JSONConversion.h"

using json = nlohmann::json;

void EventHandler::sendEvent(const Socket &socket, const ClientEvent &event) {
    json json_event = event;
    socket.sendWithSize(json_event.dump());
}

void EventHandler::sendEvent(const Socket &socket, const GameConfigurationEvent &event) {
    json json_event = event;
    socket.sendWithSize(json_event.dump());
}

void EventHandler::sendEvent(const Socket &socket, const GameStatusEvent &event) {
    json json_event = event;
    socket.sendWithSize(json_event.dump());
}

void EventHandler::sendEvent(const Socket &socket, const NotificationEvent &event) {
    json json_event = event;
    socket.sendWithSize(json_event.dump());
}

ClientEvent EventHandler::receiveEvent(const Socket &socket) {
    std::string msg;
    socket.receiveWithSize(msg);
    json message = json::parse(msg);
    ClientEvent event;
    message.get_to(event);
    return event;
}

GameConfigurationEvent EventHandler::receiveGameConfigurationEvent(const Socket &socket) {
    std::string msg;
    socket.receiveWithSize(msg);
    json message = json::parse(msg);
    GameConfigurationEvent event;
    message.get_to(event);
    return event;
}

GameStatusEvent EventHandler::receiveGameStatusEvent(const Socket &socket) {
    std::string msg;
    socket.receiveWithSize(msg);
    json message = json::parse(msg);
    GameStatusEvent event;
    message.get_to(event);
    return event;
}

NotificationEvent EventHandler::receiveNotificationEvent(const Socket &socket) {
    std::string msg;
    socket.receiveWithSize(msg);
    json message = json::parse(msg);
    NotificationEvent event;
    message.get_to(event);
    return event;
}
