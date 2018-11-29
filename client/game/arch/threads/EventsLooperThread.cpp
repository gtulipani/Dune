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

EventsLooperThread::EventsLooperThread(shaque<GameStatusEvent> &game_status_events, BlockingQueue<ClientEvent> &output_messages, bool &game_ended) :
        game_status_events(game_status_events),
        output_messages(output_messages),
        game_ended(game_ended) {}

void EventsLooperThread::pushEvent(int client_event_type, int picturable_id, Point click_position, Point release_position) {
    output_messages.push(ClientEvent(this->player_id, client_event_type, picturable_id, std::move(click_position), std::move(release_position)));
}

void EventsLooperThread::processServerEvents() {
    std::list<GameStatusEvent> events = game_status_events.popAll();
    std::for_each(events.begin(), events.end(), [this](GameStatusEvent &event){
        // Append both picturables and selectables
        std::vector<Picturable> picturables(event.picturables);
        picturables.insert(
                std::end(picturables),
                std::begin(event.selectedObjects),
                std::end(event.selectedObjects));

        window_controller.processPicturables(picturables);
    });
}

void EventsLooperThread::processMouseClickEvent(SDL_Event &event) {
    auto &mouse_event = (SDL_MouseButtonEvent &) event;
    window_controller.parseMouseClick(mouse_event, this, &EventsLooperThread::pushEvent);
}

void EventsLooperThread::processMouseReleaseEvent(SDL_Event &event) {
    auto &mouse_event = (SDL_MouseButtonEvent &) event;
    window_controller.parseMouseRelease(mouse_event, this, &EventsLooperThread::pushEvent);
}

void EventsLooperThread::processKeyDownEvent(SDL_Event &event) {
    auto &key_event = (SDL_KeyboardEvent &) event;
    switch (key_event.keysym.sym) {
        case SDLK_LEFT: {
            window_controller.move(LEFT);
            break;
        }
        case SDLK_RIGHT: {
            window_controller.move(RIGHT);
            break;
        }
        case SDLK_UP: {
            window_controller.move(UP);
            break;
        }
        case SDLK_DOWN: {
            window_controller.move(DOWN);
            break;
        }
        default:
            break;
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

            SDL_Event event;
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN: {
                    processKeyDownEvent(event);
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

            processServerEvents();

            window_controller.refresh();

            auto end = std::chrono::steady_clock::now();
            auto execution_difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::this_thread::sleep_for(std::chrono::milliseconds(
                    execution_difference > MAXIMUM_SLEEP_TIME
                    ? MAXIMUM_SLEEP_TIME
                    : MAXIMUM_SLEEP_TIME - execution_difference));

            if (game_ended) {
                this->stop();
            }
        }
    } catch (std::exception& e) {
        std::cout << "Exception in EventsLooperThread: " << e.what() << std::endl;
    }
}
