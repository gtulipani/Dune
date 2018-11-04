// STL Libraries
#include <iostream>

// Client Libraries
#include "Client.h"
#include "SdlWindow.h"

int main(int argc, char *argv[]) {
	std::cout << "Hello, World! I'm a Client!" << std::endl;

	// Client receives two parameters: the host and the port to connect to
	Client client(argv[1], argv[2]);
	client.start();
	return 0;
}
