// STL Libraries
#include <iostream>

// Client Libraries
#include "game/arch/Client.h"
#include "game/arch/threads/EventsReceptorThread.h"
#include "game/sdl/SdlWindow.h"


int main(int argc, char *argv[]) {
	// Client receives two parameters: the host and the port to connect to
	Client client(argv[1], argv[2]);
	client.start();
	return 0;
}
