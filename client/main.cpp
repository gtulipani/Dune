#include <iostream>
#include "../commons/Socket.h"

int main() {
	std::cout << "Hello, World! I'm a Client!" << std::endl;
	Socket socket("localhost", "8080");
	socket.connect();
	socket.sendInt32(5);
	socket.sendStr("Hola!");
	int32_t n = socket.receiveInt32();
	std::string msg;
	socket.receiveStr(msg, n);
	std::cout << msg << std::endl;
	socket.shutDown();
	return 0;
}
