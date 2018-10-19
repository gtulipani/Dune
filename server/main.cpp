#include <iostream>
#include <string>
#include "Accepter.h"
#include "PathFinder.h"

#define EXIT_CHAR 'q'

int main() {
	std::cout << "Hello, World! I'm a Server" << std::endl;
	testPathFinder();

	Accepter accepter("8080");
	accepter.start();

	char q;
	do {
		std::cin >> q;
	} while(q != EXIT_CHAR);

	accepter.stop();
	accepter.join();

	return 0;
}