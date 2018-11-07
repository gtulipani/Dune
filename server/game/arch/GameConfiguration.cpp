#include <fstream>

#include "json/JSONUtils.h"
#include "GameConfiguration.h"

#define CONFIGURATION_BUILDINGS_KEY "buildings"
#define CONFIGURATION_WEAPONS_KEY "weapons"
#define CONFIGURATION_SOLDIERS_KEY "soldiers"
#define CONFIGURATION_VEHICLES_KEY "vehicles"

/**
 * Private function that knows how to parse the building from the JSON
 * @param buildings_json {@link json}
 */
vector<Building>
GameConfiguration::parseBuildingsConfiguration(json &buildings_json) {
	vector<Building> buildings;
	// Iterate through all the buildings
	for (map<string, json> building_fields : buildings_json) {
		for (auto &kv : building_fields) {
			// Assign the name to the building
			Building building;
			kv.second["name"] = kv.first;
			kv.second.get_to(building);
			buildings.push_back(building);
		}
	}
	return buildings;
}

vector<Weapon> GameConfiguration::parseWeaponsConfiguration(
		json &weapons_json) {
	vector<Weapon> weapons;
	// Iterate through all the weapons
	for (map<string, json> weapon_fields : weapons_json) {
		for (auto &kv : weapon_fields) {
			// Assign the name to the weapon
			Weapon weapon;
			kv.second["name"] = kv.first;
			kv.second.get_to(weapon);
			weapons.push_back(weapon);
		}
	}
	return weapons;
}

vector<Soldier> GameConfiguration::parseSoldiersConfiguration(
		json &soldiers_json) {
	vector<Soldier> soldiers;
	// Iterate through all the soldiers
	for (map<string, json> soldier_fields : soldiers_json) {
		for (auto &kv : soldier_fields) {
			// Assign the name to the soldiers
			Soldier soldier;
			kv.second["name"] = kv.first;
			kv.second.get_to(soldier);
			soldiers.push_back(soldier);
		}
	}
	return soldiers;
}

vector<Vehicle>
GameConfiguration::parseVehiclesConfiguration(json &vehicles_json) {
	vector<Vehicle> vehicles;
	// Iterate through all the vehicles
	for (map<string, json> vehicle_fields : vehicles_json) {
		for (auto &kv : vehicle_fields) {
			// Assign the name to the vehicle
			Vehicle vehicle;
			kv.second["name"] = kv.first;
			kv.second.get_to(vehicle);
			vehicles.push_back(vehicle);
		}
	}
	return vehicles;
}

/**
 * Private function that iterates over the main keys from the JSON and
 * executhe corresponding parsing function
 * @param configuration_json {@link json}
 */
void GameConfiguration::parseGameConfiguration(json &configuration_json) {
	for (json::iterator it = configuration_json.begin();
		 it != configuration_json.end(); ++it) {
		if (it.key() == CONFIGURATION_BUILDINGS_KEY) {
			buildings = parseBuildingsConfiguration(it.value());
		} else if (it.key() == CONFIGURATION_WEAPONS_KEY) {
			weapons = parseWeaponsConfiguration(it.value());
		} else if (it.key() == CONFIGURATION_SOLDIERS_KEY) {
			soldiers = parseSoldiersConfiguration(it.value());
		} else if (it.key() == CONFIGURATION_VEHICLES_KEY) {
			vehicles = parseVehiclesConfiguration(it.value());
		}
	}
}

GameConfiguration::GameConfiguration(const string &config_file_path) {
	json game_items_configuration = json_utils::parseAsJson(config_file_path);
	parseGameConfiguration(game_items_configuration);
}

// JSON required functions
void to_json(json &j, const Building &b) {
	j = json{
			{"name",             b.name},
			{"energy",           b.energy},
			{"cost",             b.cost},
			{"size",             b.size},
			{"structure_points", b.structure_points},
			{"capacity",         b.capacity}
	};
}

void from_json(const json &j, Building &b) {
	j.at("name").get_to(b.name);
	j.at("energy").get_to(b.energy);
	j.at("cost").get_to(b.cost);
	j.at("size").get_to(b.size);
	j.at("structure_points").get_to(b.structure_points);
	j.at("capacity").get_to(b.capacity);
}

void to_json(json &j, const Vehicle &v) {
	j = json{
			{"name",       v.name},
			{"level",      v.level},
			{"speed",      v.speed},
			{"build_time", v.build_time},
			{"cost",       v.cost},
			{"life",       v.life}
	};
}

void from_json(const json &j, Vehicle &v) {
	j.at("name").get_to(v.name);
	j.at("level").get_to(v.level);
	j.at("speed").get_to(v.speed);
	j.at("build_time").get_to(v.build_time);
	j.at("cost").get_to(v.cost);
	j.at("life").get_to(v.life);
}

void to_json(json &j, const Weapon &w) {
	j = json{
			{"name",            w.name},
			{"damage",          w.damage},
			{"shoot_frequency", w.shoot_frequency},
			{"bonus",           w.bonus}
	};
}

void from_json(const json &j, Weapon &w) {
	j.at("name").get_to(w.name);
	j.at("damage").get_to(w.damage);
	j.at("shoot_frequency").get_to(w.shoot_frequency);
	j.at("bonus").get_to(w.bonus);
}

void to_json(json &j, const Soldier &s) {
	j = json{
			{"name",          s.name},
			{"level",         s.level},
			{"speed",         s.speed},
			{"training_time", s.training_time},
			{"cost",          s.cost},
			{"life",          s.life}
	};
}

void from_json(const json &j, Soldier &s) {
	j.at("name").get_to(s.name);
	j.at("level").get_to(s.level);
	j.at("speed").get_to(s.speed);
	j.at("training_time").get_to(s.training_time);
	j.at("cost").get_to(s.cost);
	j.at("life").get_to(s.life);
}
