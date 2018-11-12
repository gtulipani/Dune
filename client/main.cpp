// STL Libraries
#include <iostream>

// Client Libraries
#include "game/arch/Client.h"
#include "game/arch/EventsReceptorThread.h"
#include "game/sdl/SdlWindow.h"


int main(int argc, char *argv[]) {
	std::cout << "Hello, World! I'm a Client!" << std::endl;

	// EventsReceptorThread receives two parameters: the host and the port to connect to
	Client client(argv[1], argv[2]);
	client.start();
	return 0;
}
