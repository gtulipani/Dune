#include "EventsLooperThread.h"

// STL Libraries
#include <chrono>
#include <iostream>
#include <utility>
#include <functional>

// Commons Libraries
#include <events/EventHandler.h>
#include <TileUtils.h>

// SDL Libraries
#include <SDL2/SDL_events.h>

#define MAXIMUM_SLEEP_TIME std::chrono::milliseconds(30)

EventsLooperThread::EventsLooperThread(shaque<GameStatusEvent> &game_status_events, BlockingQueue<ClientEvent> &output_messages) :
        game_status_events(game_status_events),
        output_messages(output_messages) {}

void EventsLooperThread::pushEvent(std::string message, Point click_position, Point release_position) {
    output_messages.push(ClientEvent(this->player_id, std::move(message), std::move(click_position), std::move(release_position)));
}

bool EventsLooperThread::processServerEvents() {
    bool something_changed = false;
    std::list<GameStatusEvent> events = game_status_events.popAll();
    if (!events.empty()) {
        something_changed = true;
    }
    std::for_each(events.begin(), events.end(), [this](GameStatusEvent &event){
        window_controller.processPicturables(event.picturables);
    });
    return something_changed;
}

void EventsLooperThread::processMouseClickEvent(SDL_Event &event) {
    auto &mouse_event = (SDL_MouseButtonEvent &) event;
    window_controller.parseMouseClick(mouse_event, this, &EventsLooperThread::pushEvent);
}

void EventsLooperThread::processMouseReleaseEvent(SDL_Event &event) {
    auto &mouse_event = (SDL_MouseButtonEvent &) event;
    window_controller.parseMouseRelease(mouse_event, this, &EventsLooperThread::pushEvent);
}

bool EventsLooperThread::processKeyDownEvent(SDL_Event &event) {
    auto &key_event = (SDL_KeyboardEvent &) event;
    switch (key_event.keysym.sym) {
        case SDLK_LEFT:
            return window_controller.move(LEFT);
        case SDLK_RIGHT:
            return window_controller.move(RIGHT);
            break;
        case SDLK_UP:
            return window_controller.move(UP);
        case SDLK_DOWN:
            return window_controller.move(DOWN);
        default:
            return false;
    }
}

void EventsLooperThread::configure(unsigned int player_id, Matrix matrix) {
    this->player_id = player_id;
    this->window_controller.configure(std::move(matrix));
}

void EventsLooperThread::run() {
    try {
        window_controller.fill();

        // Process events received from the socket
        processServerEvents();

        window_controller.render();

        while (this->isRunning()) {
            auto start = std::chrono::steady_clock::now();
            bool something_changed = false;

            SDL_Event event;
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN: {
                    something_changed = processKeyDownEvent(event);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    processMouseClickEvent(event);
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    processMouseReleaseEvent(event);
                    break;
                }
                case SDL_QUIT: {
                    this->stop();
                }
                default:
                    break;
            }

            // If nothing changed then we don't need to re-render
            something_changed = (something_changed || processServerEvents());

            if (something_changed) {
                //window_controller.fill();
                window_controller.refreshMap();
            }

            auto end = std::chrono::steady_clock::now();
            auto execution_difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::this_thread::sleep_for(std::chrono::milliseconds(
                    execution_difference > MAXIMUM_SLEEP_TIME
                    ? MAXIMUM_SLEEP_TIME
                    : MAXIMUM_SLEEP_TIME - execution_difference));
        }
    } catch (std::exception& e) {
        std::cout << "Exception in EventsLooperThread: " << e.what() << std::endl;
    }
}
