#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "game/arch/ServerThread.h"

#define EXIT_CHAR 'q'

int main(int argc, char *argv[]) {
	std::cout << "Hello, World! I'm a Server" << std::endl;

	// Server receives a key-value file with the configuration
	ServerThread server(argv[1]);
	server.start();

	while (std::cin.peek() != EXIT_CHAR) {}

	server.stop();
	server.join();

	return 0;
}
