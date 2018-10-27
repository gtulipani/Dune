#include <iostream>
#include <SDL.h>
#include "../commons/Socket.h"
#include "SdlWindow.h"
#include "SdlTexture.h"

int main() {
	std::cout << "Hello, World! I'm a Client!" << std::endl;
	Socket socket("localhost", "8080");
	socket.connect();
	socket.sendInt32(5);
	socket.sendStr("Hola!");
	/*int32_t n = socket.receiveInt32();
	std::string msg;
	socket.receiveStr(msg, n);
	std::cout << msg << std::endl;*/
	try {
		SdlWindow window(800, 600);
		window.fill();
		// Usar factory
		SdlTexture im("cat.gif", window);
		Area srcArea(0, 0, 300, 300);
		bool running = true;
		int x = 100;
		int y = 100;
		while (running) {
			SDL_Event event;
			Area destArea(x, y, 300, 300);
			window.fill(); // Repinto el fondo gris
			im.render(srcArea, destArea);
			// Para el alumno: Buscar diferencia entre waitEvent y pollEvent
			SDL_WaitEvent(&event);
			switch(event.type) {
				case SDL_KEYDOWN: {
					SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
					switch (keyEvent.keysym.sym) {
						case SDLK_LEFT:
							x -= 10;
							break;
						case SDLK_RIGHT:
							x += 10;
							break;
						case SDLK_UP:
							y -= 10;
							break;
						case SDLK_DOWN:
							y += 10;
							break;
					}
				} // Fin KEY_DOWN
					break;
				case SDL_MOUSEMOTION:
					std::cout << "Oh! Mouse" << std::endl;
					break;
				case SDL_QUIT:
					std::cout << "Quit :(" << std::endl;
					running = false;
					break;
			}
			window.render();
		}
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	socket.shutDown();
	return 0;
}
