#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Server.h"
#include "shaque.h"
#include "Accepter.h"

#define KEY_VALUE_SEPARATOR '='
#define EXIT_CHAR 'q'

#define PORT_KEY "port"
#define MAPS_PATH_KEY "maps_path"
#define UNITS_PROPERTIES_PATH_KEY "units_properties_file_path"

const vector<string> Server::VALID_KEYS = {
		PORT_KEY,
		MAPS_PATH_KEY,
		UNITS_PROPERTIES_PATH_KEY
};

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

Server::Server(string port, string maps_path, GameConfiguration game_configuration) :
		port(move(port)),
		maps_path(move(maps_path)),
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
	Accepter accepter(port, 5);
	accepter.start();

	while (std::cin.peek() != EXIT_CHAR) {}

	accepter.stop();
	accepter.join();
}
