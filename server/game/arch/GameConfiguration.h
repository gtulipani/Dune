#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

#include <string>

#include "json.hpp"
#include "game/model/Building.h"
#include "game/model/Vehicle.h"
#include "game/model/Weapon.h"
#include "game/model/Soldier.h"

using namespace std;

class GameConfiguration {
private:
	vector<Building> buildings;
	vector<Weapon> weapons;
	vector<Soldier> soldiers;
	vector<Vehicle> vehicles;

	vector<Building> parseBuildingsConfiguration(json &buildings_json);

	vector<Weapon> parseWeaponsConfiguration(json &configuration_json);

	vector<Soldier> parseSoldiersConfiguration(json &configuration_json);

	vector<Vehicle> parseVehiclesConfiguration(json &configuration_json);

	void parseGameConfiguration(json &configuration_json);

	json parseAsJson(const string &game_units_parameters_path);

public:
	explicit GameConfiguration(const string &config_file_path);
};


#endif //__GAME_CONFIGURATION_H__
