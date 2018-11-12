#include <utility>

#include "GameThread.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/EventHandler.h>
#include <TileUtils.h>

// SDL Libraries
#include <SDL.h>

GameThread::GameThread(shaque<GameStatusEvent> &game_status_events, shaque<ClientEvent> &output_messages) :
        game_status_events(game_status_events),
        output_messages(output_messages) {}

void GameThread::pushEvent(std::string message, Point position) {
    output_messages.push(ClientEvent(1, std::move(message), std::move(position)));
}

void GameThread::processEvents() {
    std::list<GameStatusEvent> events = game_status_events.popAll();
    std::for_each(events.begin(), events.end(), [this](GameStatusEvent &event){
        main_window.processPicturables(event.picturables);
    });
}

void GameThread::processMouseEvent(SDL_Event &event) {
    auto &mouse_event = (SDL_MouseButtonEvent &) event;
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            pushEvent(LEFT_CLICK_TYPE, Point(mouse_event.x, mouse_event.y));
            break;
        }
        case SDL_BUTTON_RIGHT: {
            pushEvent(RIGHT_CLICK_TYPE, Point(mouse_event.x, mouse_event.y));
        }
        default:
            break;
    }
}

void GameThread::processKeyDownEvent(SDL_Event &event) {
    auto &key_event = (SDL_KeyboardEvent &) event;
    switch (key_event.keysym.sym) {
        case SDLK_LEFT:
            main_window.move(LEFT);
            break;
        case SDLK_RIGHT:
            main_window.move(RIGHT);
            break;
        case SDLK_UP:
            main_window.move(UP);
            break;
        case SDLK_DOWN:
            main_window.move(DOWN);
            break;
        default:
            break;
    }
}

void GameThread::configure(Matrix matrix) {
    this->terrain_matrix = std::move(matrix);
    //main_window.configure(std::move(matrix));
}

void GameThread::run() {
    try {
        main_window.configure(terrain_matrix);
        main_window.fill();

        // Create initial unit in position 0,0
        pushEvent(CREATE_WALKING_UNIT_TYPE, Point(0, 0));

        // Process events received from the socket
        processEvents();

        main_window.render();

        while (this->isRunning()) {
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
                    std::cout << "Quit :(" << std::endl;
                    this->stop();
                    break;
                default:
                    break;
            }
            main_window.fill();
            processEvents();
            main_window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
