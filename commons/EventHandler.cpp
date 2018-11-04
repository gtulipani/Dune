#include "EventHandler.h"

// Commons Libraries
#include "Socket.h"
#include "json.hpp"
#include "JSONConversion.h"

using json = nlohmann::json;

void EventHandler::sendEvent(const Socket &socket, const Event &event) {
    json json_event = event;
    std::string msg = json_event.dump();
    socket.sendInt32(msg.length());
    socket.sendStr(msg);
}

Event EventHandler::receiveEvent(const Socket &socket) {
    int32_t n = socket.receiveInt32();
    std::string msg;
    socket.receiveStr(msg, n);
    json message = json::parse(msg);
    Event event;
    message.get_to(event);
    return event;
}
