#include <utility>

#include "Game.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/EventHandler.h>
#include <TileUtils.h>

// SDL Libraries
#include <SDL.h>

void Game::sendEvent(std::string message, Point position) {
    EventHandler::sendEvent(socket, ClientEvent(1, std::move(message), std::move(position)));
}

void Game::processMouseEvent(SDL_Event& event) {
    auto & mouse_event = (SDL_MouseButtonEvent&) event;
    switch (mouse_event.button) {
        case SDL_BUTTON_LEFT: {
            sendEvent(LEFT_CLICK_TYPE, tile_utils::getTileFromPixel(Point(mouse_event.x, mouse_event.y)));
            break;
        }
        case SDL_BUTTON_RIGHT: {
            sendEvent(RIGHT_CLICK_TYPE, tile_utils::getTileFromPixel(Point(mouse_event.x, mouse_event.y)));
        }
        default:
            break;
    }
}

void Game::processKeyDownEvent(SDL_Event& event) {
    auto & key_event = (SDL_KeyboardEvent&) event;
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

void Game::processEventFromSocket() {
    NotificationEvent notification_event = EventHandler::receiveNotificationEvent(socket);
    if (notification_event.message == GAME_STATUS_EVENT) {
        GameStatusEvent event = EventHandler::receiveGameStatusEvent(socket);
        main_window.processPicturables(event.picturables);
    }
}

Matrix Game::receiveMatrix() {
    return EventHandler::receiveMapConfigurationEvent(socket).matrix;
}

void Game::configure(Socket socket) {
    this->socket = std::move(socket);
    main_window.configure(receiveMatrix());
}

void Game::start() {
    main_window.fill();

    // Create initial unit in position 0,0
    sendEvent(CREATE_WALKING_UNIT_TYPE, Point(0,0));

    main_window.render();

    bool running = true;
    while (running) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN: {
                processKeyDownEvent(event);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                processMouseEvent(event);
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                running = false;
                break;
            default:
                break;
        }
        main_window.fill();
        main_window.render();
    }
}
