#include "Client.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <json.hpp>
#include <Event.h>
#include <Matrix.h>
#include <EventHandler.h>
#include <TileUtils.h>

// Client Libraries
#include "Client.h"
#include "SdlTexture.h"
#include "SdlWindow.h"

// SDL Libraries
#include <SDL.h>

#define TILE_PIXEL_RATE 10

#define TERRAIN_RESOURCES_PATH string("resources/images/game/terrain")

using nlohmann::json;

void Client::loadTerrainMatrix() {
    MapConfigurationEvent event = EventHandler::receiveMapConfigurationEvent(socket);
    matrix = event.matrix;
}

void Client::waitForGameStart() {
    while (!game_started) {
        Event event = EventHandler::receiveEvent(socket);
        game_started = (event.type == GAME_STARTED_EVENT);
    }
}

Client::Client(string host, string port) : host(move(host)), port(move(port)), game_started(false) {}

void Client::start() {
    socket = Socket(host, port);
    socket.connect();

    try {
        waitForGameStart();
        loadTerrainMatrix();

        width = matrix.cols();
        height = matrix.rows();
        window = SdlWindow(width * TILE_PIXEL_RATE, height * TILE_PIXEL_RATE);
        window.fill();

        SdlTexture arena(TERRAIN_RESOURCES_PATH + "/Arena.png", window);
        SdlTexture cimas(TERRAIN_RESOURCES_PATH + "/Cimas.png", window);
        SdlTexture dunas(TERRAIN_RESOURCES_PATH + "/Dunas.png", window);
        SdlTexture especia(TERRAIN_RESOURCES_PATH + "/Especia.png", window);
        SdlTexture precipicio(TERRAIN_RESOURCES_PATH + "/Precipicio.png", window);
        SdlTexture roca(TERRAIN_RESOURCES_PATH + "/Roca.png", window);

        terrain_render_map = {
                {ARENA, arena},
                {CIMAS, cimas},
                {DUNAS, dunas},
                {ESPECIA, especia},
                {PRECIPICIOS, precipicio},
                {ROCA, roca}
        };

        // x, y, width, height
        int offset_x = 0;
        int offset_y = 0;
        Area srcArea(offset_x, offset_y, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
        bool running = true;

        while (running) {
            SDL_Event event;

            window.fill();

            // Render the terrain matrix
            for (int col = 0; col < width; col++) {
                for (int row = 0; row < height; row++) {
                    Area destArea((TILE_PIXEL_RATE * col) + offset_x, (TILE_PIXEL_RATE * row) + offset_y, TILE_PIXEL_RATE, TILE_PIXEL_RATE);
                    auto it = terrain_render_map.find(matrix.at(row, col));
                    if (it != terrain_render_map.end()) {
                        it->second.render(srcArea, destArea);
                    }
                }
            }

            SDL_WaitEvent(&event);
            switch(event.type) {
                case SDL_KEYDOWN: {
                    auto & keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            offset_x -= TILE_PIXEL_RATE;
                            break;
                        case SDLK_RIGHT:
                            offset_x += TILE_PIXEL_RATE;
                            break;
                        case SDLK_UP:
                            offset_y -= TILE_PIXEL_RATE;
                            break;
                        case SDLK_DOWN:
                            offset_y += TILE_PIXEL_RATE;
                            break;
                        default:
                            break;
                    }
                }
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << "Oh! Mouse" << std::endl;
                    break;
                case SDL_QUIT:
                    std::cout << "Quit :(" << std::endl;
                    running = false;
                    break;
                default:
                    break;
            }
            window.render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    socket.shutDown();

    std::cout << "Client ended" << std::endl;
}
