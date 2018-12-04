// STL Libraries
#include <iostream>

// Client Libraries
#include "game/arch/Client.h"
#include "game/arch/threads/EventsReceptorThread.h"
#include "game/sdl/SdlWindow.h"

#define HELP_COMMAND "-h"
#define LONG_HELP_COMMAND "--help"

int main(int argc, char *argv[]) {
	if ((argc < 2) || (argc > 3)) {
		std::cout << "Debe ingresar host y puerto. Ingrese -h para obtener ayuda" << std::endl;
		return 0;
	}

	std::string command = argv[1];

	if (command == HELP_COMMAND || command == LONG_HELP_COMMAND) {
		std::cout << "Este es el cliente del juego Dune Online" << std::endl;
		std::cout << "Para jugar, asegúrese que el servidor esté corriendo." << std::endl;
		std::cout << "El cliente debe ejecutarse con el host y el puerto como parámetros. Ejemplo:" << std::endl;
		std::cout << "- client localhost 8080" << std::endl;
		return 0;
	}

	// Client receives two parameters: the host and the port to connect to
	Client client(argv[1], argv[2]);
	client.start();
	return 0;
}
