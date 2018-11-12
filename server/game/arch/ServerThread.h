#ifndef __SERVER_H__
#define __SERVER_H__

// STD Libraries
#include <string>
#include <vector>
#include <map>

// Commons Libraries
#include <json/json.hpp>
#include <events/ClientEvent.h>
#include <Thread.h>

// Server Libraries
#include "ConfigMap.h"
#include "GameConfiguration.h"
#include "Accepter.h"
#include "Game.h"

using json = nlohmann::json;

class ServerThread : public Thread {
private:
	ConfigMap configMap;
	GameConfiguration gameConfig;
	std::vector<std::string> mapsList;
	std::vector<ClientThread*> clients;
	Accepter accepter;
	std::mutex m;
	shaque<ClientEvent> sharedQueue;
	Game game;

	bool hasExpectedExtension(const std::string &file_to_add);

	vector<string> getFilesFromPath(const std::string &path);

	void run() override;

	void terminate() override;

public:
	explicit ServerThread(const std::string &config_file_path);
};


#endif //__SERVER_H__
