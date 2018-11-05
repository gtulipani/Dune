#include "Server.h"

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
#include <Unit.h>
#include <Event.h>

// Server Libraries
#include "shaque.h"
#include "AccepterThread.h"

#define KEY_VALUE_SEPARATOR '='
#define EXIT_CHAR 'q'
#define PORT_KEY "port"
#define MAPS_PATH_KEY "maps_path"
#define UNITS_PROPERTIES_PATH_KEY "units_properties_file_path"

const string MAP_EXTENSION = ".map";

const vector<string> Server::VALID_KEYS = {
		PORT_KEY,
		MAPS_PATH_KEY,
		UNITS_PROPERTIES_PATH_KEY
};

/**
 * Private function that checks the extension from each file parsed in the
 * directory
 */
bool Server::hasExpectedExtension(const string &file_to_add) {
	return (file_to_add.size() >= MAP_EXTENSION.size() &&
			file_to_add.compare(file_to_add.size() - MAP_EXTENSION.size(),
								MAP_EXTENSION.size(), MAP_EXTENSION) == 0);
}

/**
 * Private function that gets the names of all the files existing in the path
 * passed as parameter in UNIX
 */
vector<string> Server::getFilesFromPath(const string &path) {
	vector<string> files;
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

/**
 * Private function that creates a ConfigMap based on a file of key values
 * @param config_file_path {@link std::string} with the path
 */
ConfigMap Server::parseConfigurationFile(const string &config_file_path) {
	fstream input_stream;
	input_stream.open(config_file_path, ios::in);
	ConfigMap key_values_map;
	string line;
	while (getline(input_stream, line)) {
		istringstream is_line(line);
		string key;
		if (getline(is_line, key, KEY_VALUE_SEPARATOR)) {
			string value;
			if (getline(is_line, value)) {
				key_values_map[key] = value;
			}
		}
	}
	input_stream.close();
	return key_values_map;
}

Server::Server(string port, string maps_path,
			   GameConfiguration game_configuration) :
		port(move(port)),
		maps_list(getFilesFromPath(maps_path)),
		game_configuration(move(game_configuration)) {}

Server::Server(ConfigMap config_map) : Server(
		move(config_map[PORT_KEY]),
		move(config_map[MAPS_PATH_KEY]),
		GameConfiguration(config_map[UNITS_PROPERTIES_PATH_KEY])) {
	if (config_map.size() < VALID_KEYS.size()) {
		throw runtime_error("Mandatory parameters missing");
	}
}

Server::Server(const std::string &config_map_file_path) :
		Server(parseConfigurationFile(config_map_file_path)) {}

void Server::start() {
	AccepterThread accepter(port, 1);
	accepter.start();

	while (std::cin.peek() != EXIT_CHAR) {}

	accepter.stop();
	accepter.join();
}
