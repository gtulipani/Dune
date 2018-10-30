#include <QApplication>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include "editor/include/Editor.h"
#include "game/arch/shaque.h"
#include "game/arch/Accepter.h"

#define EXIT_CHAR 'q'

int main(int argc, char *argv[]) {
	if (std::string(argv[1]) == "editor") {
		// Clase que contiene el loop principal
		QApplication app(argc, argv);
		// Instancio el greeter
		Editor editor;
		editor.show();
		// Arranca el loop de la UI
		return app.exec();
	} else {
		std::cout << "Hello, World! I'm a Server" << std::endl;

		Accepter accepter("8080", 5);
		accepter.start();

		while (std::cin.peek() != EXIT_CHAR) {}

		accepter.stop();
		accepter.join();
	}
	return 0;
}
