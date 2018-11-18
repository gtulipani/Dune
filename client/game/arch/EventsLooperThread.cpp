#include "EventsLooperThread.h"

// STL Libraries
#include <chrono>
#include <iostream>
#include <utility>

// Commons Libraries
#include <events/EventHandler.h>
#include <TileUtils.h>

// SDL Libraries
#include <SDL2/SDL_events.h>

#define MAXIMUM_SLEEP_TIME std::chrono::milliseconds(30)

EventsLooperThread::EventsLooperThread(shaque<GameStatusEvent> &game_status_events, BlockingQueue<ClientEvent> &output_messages) :
        game_status_events(game_status_events),
        output_messages(output_messages) {}

void EventsLooperThread::pushEvent(std::string message, Point position) {
    output_messages.push(ClientEvent(1, std::move(message), std::move(position)));
}

void EventsLooperThread::processServerEvents() {
    std::list<GameStatusEvent> events = game_status_events.popAll();
    std::for_each(events.begin(), events.end(), [this](GameStatusEvent &event){
        window_controller.processPicturables(event.picturables);
    });
}

void EventsLooperThread::processMouseEvent(SDL_Event &event) {
    auto &mouse_event = (SDL_MouseButtonEvent &) event;
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            pushEvent(LEFT_CLICK_TYPE, window_controller.getRelativePoint(mouse_event.y, mouse_event.x));
            break;
        }
        case SDL_BUTTON_RIGHT: {
            pushEvent(RIGHT_CLICK_TYPE, window_controller.getRelativePoint(mouse_event.y, mouse_event.x));
        }
        default:
            break;
    }
}

void EventsLooperThread::processKeyDownEvent(SDL_Event &event) {
    auto &key_event = (SDL_KeyboardEvent &) event;
    switch (key_event.keysym.sym) {
        case SDLK_LEFT:
            window_controller.move(LEFT);
            break;
        case SDLK_RIGHT:
            window_controller.move(RIGHT);
            break;
        case SDLK_UP:
            window_controller.move(UP);
            break;
        case SDLK_DOWN:
            window_controller.move(DOWN);
            break;
        default:
            break;
    }
}

void EventsLooperThread::configure(Matrix matrix) {
    this->window_controller.configure(std::move(matrix));
}

void EventsLooperThread::run() {
    try {
        window_controller.fill();

        // Create initial unit in position 0,0
        pushEvent(CREATE_WALKING_UNIT_TYPE, Point(0, 0));

        // Process events received from the socket
        processServerEvents();

        window_controller.render();

        while (this->isRunning()) {
            auto start = std::chrono::steady_clock::now();
            // Calcular tiempo que tarda el ciclo y restarle eso al tiempo de sleep
            SDL_Event event;
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN: {
                    processKeyDownEvent(event);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                    processMouseEvent(event);
                    break;
                case SDL_QUIT:
                    this->stop();
                default:
                    break;
            }
            window_controller.fill();
            processServerEvents();
            window_controller.render();

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
