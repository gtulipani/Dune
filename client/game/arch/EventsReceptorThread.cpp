#include "EventsReceptorThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json/json.hpp>
#include <Matrix.h>
#include <SOException.h>
#include <TileUtils.h>
#include <events/EventHandler.h>
#include <events/NotificationEvent.h>

// Client Libraries
#include "EventsReceptorThread.h"
#include "../sdl/SdlTexture.h"
#include "../sdl/SdlWindow.h"

using nlohmann::json;

EventsReceptorThread::EventsReceptorThread(Socket &socket, shaque<GameStatusEvent> &game_status_events) :
    socket(socket),
    game_status_events(game_status_events) {}

void EventsReceptorThread::run() {
    try {
        while (this->isRunning()) {
            NotificationEvent notification_event = EventHandler::receiveNotificationEvent(socket);
            if (notification_event.message == GAME_STATUS_EVENT) {
                GameStatusEvent event = EventHandler::receiveGameStatusEvent(socket);
                game_status_events.push(event);
            }
        }
    } catch (SOException& e) {
    } catch (std::exception& e) {
        std::cout << "Exception in EventsReceptorThread: " << e.what() << std::endl;
    }
}

void EventsReceptorThread::terminate() {
    this->stop();
}