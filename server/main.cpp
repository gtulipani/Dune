#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "game/arch/ServerThread.h"

#define EXIT_CHAR 'q'

int main(int argc, char *argv[]) {
	// Server receives a key-value file with the configuration
	ServerThread server(argv[1]);

	try {
		server.start();
	} catch (const std::exception& e) {
		std::cout << "an unexpected error has occurred.. :(" << std::endl;
	}

	while (std::cin.peek() != EXIT_CHAR) {}

	server.stop();
	server.join();

	return 0;
}
