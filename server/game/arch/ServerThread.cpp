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
#define MAPS_PATH_KEY "maps_path"
#define UNITS_PROPERTIES_PATH_KEY "units_properties_file_path"
#define GAME_SIZE_KEY "game_size"

const string MAP_EXTENSION = ".map";

/**
 * Private function that checks the extension from each file parsed in the
 * directory
 */
bool ServerThread::hasExpectedExtension(const std::string &file_to_add) {
	return (file_to_add.size() >= MAP_EXTENSION.size() &&
			file_to_add.compare(file_to_add.size() - MAP_EXTENSION.size(),
								MAP_EXTENSION.size(), MAP_EXTENSION) == 0);
}

/**
 * Private function that gets the names of all the files existing in the path
 * passed as parameter in UNIX
 */
std::vector<std::string> ServerThread::getFilesFromPath(const std::string &path) {
	std::vector<std::string> files;
	DIR *dirp = opendir(path.c_str());
	struct dirent *dp;
	while ((dp = readdir(dirp)) != nullptr) {
		if (hasExpectedExtension(dp->d_name)) {
			string complete_name(path);
			files.emplace_back(
					move(complete_name.append(("/")).append
					(dp->d_name)));
		}
	}
	closedir(dirp);
	return files;
}

ServerThread::ServerThread(const std::string& configMapFilePath) :
configMap(configMapFilePath),
gameConfig(configMap.at(UNITS_PROPERTIES_PATH_KEY)),
mapsList(getFilesFromPath(configMap.at(MAPS_PATH_KEY))),
accepter(configMap.at(PORT_KEY), std::stoi(configMap.at(GAME_SIZE_KEY)), clients),
sharedQueue(m),
game(sharedQueue, clients, gameConfig) {}

void ServerThread::run() {
	accepter.start(sharedQueue);
	if (!accepter.wasInterrupted()) {
		game.start();
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
