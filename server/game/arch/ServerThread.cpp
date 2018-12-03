#include "ServerThread.h"

// Standard Libraries
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>

// Libraries used for getting files from directory in POSIX
#include <sys/types.h>
#include <dirent.h>

// Commons Libraries
#include <events/ClientEvent.h>

// Server Libraries
#include "shaque.h"
#include "ClientThread.h"
#include "Accepter.h"
#include "Game.h"

#define PORT_KEY "port"
#define MAP_PATH_KEY "map_path"
#define UNITS_PROPERTIES_PATH_KEY "units_properties_file_path"
#define GAME_SIZE_KEY "game_size"

ServerThread::ServerThread(const std::string& configMapFilePath) :
configMap(configMapFilePath),
gameConfig(configMap.at(UNITS_PROPERTIES_PATH_KEY)),
accepter(configMap.at(PORT_KEY), std::stoi(configMap.at(GAME_SIZE_KEY)), clients),
sharedQueue(m),
game(sharedQueue, clients, gameConfig) {}

void ServerThread::run() {
	accepter.start(sharedQueue);
	if (!accepter.wasInterrupted()) {
		game.start(configMap.at(MAP_PATH_KEY));
	}
	for (ClientThread* client : clients) {
		client->stop();
		client->join();
		delete client;
	}
	this->stop();
}

void ServerThread::terminate() {
	accepter.stop();
	if (!accepter.wasInterrupted()) {
		game.stop();
	}
}
