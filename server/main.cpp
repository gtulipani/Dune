#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "game/arch/ServerThread.h"

#define EXIT_CHAR 'q'

#define HELP_COMMAND "-h"
#define LONG_HELP_COMMAND "--help"

int main(int argc, char *argv[]) {

	if (argc != 2) {
		std::cout << "Debe ingresar un archivo de configuracion. Ingrese -h para obtener ayuda" << std::endl;
		return 0;
	}

	std::string command = argv[1];

	if (command == HELP_COMMAND || command == LONG_HELP_COMMAND) {
		std::cout << 	"Este es el servidor del juego Dune Online" << std::endl;
		std::cout << 	"Para jugar, inicie el servidor con un archivo de" <<
						"configuracion como parametro." << std::endl;
		std::cout << 	"El archivo de configuracion debe tener el formato" <<
						"'clave=valor'. Donde las claves son:" << std::endl;
		std::cout << 	"- " << PORT_KEY << std::endl;
		std::cout << 	"- " << MAP_PATH_KEY << std::endl;
		std::cout << 	"- " << UNITS_PROPERTIES_PATH_KEY << std::endl;
		std::cout << 	"- " << GAME_SIZE_KEY << std::endl;
		std::cout <<	"Un archivo de configuracion predeterminado se" <<
						"encuentra en la carpeta raiz del proyecto:" <<
						"/server.conf" << std::endl;
		std::cout <<	"Una vez iniciado, ingrese q para salir" << std::endl;
		return 0;
	}

	// Server receives a key-value file with the configuration
	ServerThread server(argv[1]);
	try {
		server.start();
	} catch (const std::runtime_error& e) {
		std::cerr << "Runtime error: " << e.what() << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Unexpected error occurred..." << std::endl;
	} catch (...) {
		std::cerr << "Something weird happened..." << std::endl;
	}


	while (std::cin.peek() != EXIT_CHAR) {}

	server.stop();
	server.join();

	return 0;
}
