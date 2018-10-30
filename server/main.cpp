#include <QApplication>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "editor/include/Editor.h"
#include "game/arch/Server.h"

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

		// Server receives a key-value file with the configuration
		Server server(argv[1]);
		server.start();
	}
	return 0;
}
