#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include "shaque"
#include "Accepter.h"
#include "PathFinder.h"

#define EXIT_CHAR 'q'

int main() {
	std::cout << "Hello, World! I'm a Server" << std::endl;
	testPathFinder();

	std::mutex m;

	shaque<std::string> sharedQueue(m);

	Accepter accepter("8080", sharedQueue);
	accepter.start();

	char q;
	do {
		std::cin >> q;
	} while(q != EXIT_CHAR);

	accepter.stop();
	accepter.join();

	return 0;
}
