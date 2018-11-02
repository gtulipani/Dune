#include <iostream>
#include <vector>
#include <SDL.h>
#include <Terrain.h>
#include <map>
#include "Socket.h"
#include "Matrix.h"
#include "SdlWindow.h"
#include "SdlTexture.h"

#define TERRAIN_WIDTH 20
#define TERRAIN_HEIGHT 20

int main() {
	std::cout << "Hello, World! I'm a Client!" << std::endl;
    /*Socket socket("localhost", "8080");
    socket.connect();
    socket.sendInt32(5);
    socket.sendStr("Hola!");
    int32_t n = socket.receiveInt32();
    std::string msg;
    socket.receiveStr(msg, n);
    std::cout << msg << std::endl;*/
	try {
		//std::string images_base_path("resources/images/game/terrain");
		//std::string maps_path("resources/maps/base.map");
		std::string images_base_path("../../resources/images/game/terrain");
		std::string maps_path("../../resources/maps/base.map");

		Matrix matrix(maps_path);

		int map_width = matrix.cols();
		int map_height = matrix.rows();
	    SdlWindow window(map_width * TERRAIN_WIDTH, map_height * TERRAIN_HEIGHT);
		window.fill();


		// Will use the map to identify each image during rendering
        SdlTexture arena(images_base_path + "/Arena.png", window);
		SdlTexture cimas(images_base_path + "/Cimas.png", window);
		SdlTexture dunas(images_base_path + "/Dunas.png", window);
		SdlTexture especia(images_base_path + "/Especia.png", window);
		SdlTexture precipicios(images_base_path + "/Precipicio.png", window);
		SdlTexture roca(images_base_path + "/Roca.png", window);
		std::map<int, SdlTexture&> terrain_render_map = {
				{ARENA, arena},
				{CIMAS, cimas},
				{DUNAS, dunas},
				{ESPECIA, especia},
				{PRECIPICIOS, precipicios},
				{ROCA, roca}
		};

        // x, y, width, height
        int offset_x = 0;
        int offset_y = 0;
		Area srcArea(offset_x, offset_y, TERRAIN_WIDTH, TERRAIN_HEIGHT);
		bool running = true;

		while (running) {
			SDL_Event event;

			window.fill();
			// Render the terrain matrix
			for (int col = 0; col < map_width; col++) {
			    for (int row = 0; row < map_height; row++) {
                    Area destArea((TERRAIN_WIDTH * col) + offset_x, (TERRAIN_HEIGHT * row) + offset_y, TERRAIN_WIDTH, TERRAIN_HEIGHT);
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
							offset_x -= 10;
							break;
						case SDLK_RIGHT:
							offset_x += 10;
							break;
						case SDLK_UP:
							offset_y -= 10;
							break;
						case SDLK_DOWN:
							offset_y += 10;
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
		return 1;
	}
	//socket.shutDown();
	return 0;
}
