#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <vector>
#include <map>

#include "json.hpp"
#include "GameConfiguration.h"

typedef std::map<string, string> ConfigMap;

using json = nlohmann::json;
using namespace std;

class Server {
private:
	string port;
	vector<string> maps_list;
	GameConfiguration game_configuration;

	static const vector<string> VALID_KEYS;

	bool hasExpectedExtension(const string &file_to_add);

	vector<string> getFilesFromPath(const string &path);

	ConfigMap parseConfigurationFile(const string &config_file_path);

public:
	Server(string port, string maps_path, GameConfiguration game_configuration);

	explicit Server(ConfigMap configuration);

	explicit Server(const string &config_file_path);

	void start();
};


#endif //__DUNE_SERVER_H__
