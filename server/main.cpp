#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "game/arch/Server.h"

int main(int argc, char *argv[]) {
	std::cout << "Hello, World! I'm a Server" << std::endl;

	// Server receives a key-value file with the configuration
	Server server(argv[1]);
	server.start();
	return 0;
}
