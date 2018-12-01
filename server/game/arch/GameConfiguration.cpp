#include "GameConfiguration.h"

#include <json/json.hpp>
#include <json/JSONUtils.h>

#include "../model/Player.h"
#include "../model/Infanteria.h"
#include "../model/Vehiculo.h"
#include "../model/Cosechadora.h"
#include "../model/Building.h"

#include <UnitsAndBuildings.h>

#include "TileUtils.h"

#include "Sprites.h"

#define CONFIGURATION_BUILDINGS_KEY "buildings"
#define CONFIGURATION_WEAPONS_KEY "weapons"
#define CONFIGURATION_SOLDIERS_KEY "attacking_units"
#define CONFIGURATION_HARVESTER_KEY "harvester"

void GameConfiguration::parseWeapons(json& weapons_json) {
    for (json::iterator it = weapons_json.begin(); it != weapons_json.end(); ++it) {
        Weapon* weapon = new Weapon(it.key(), it.value().at("damage"), it.value().at("shot_frequency"));
        weapons[it.key()] = weapon;
    }
}

void GameConfiguration::parseAttackingUnitsConfig(json& attacking_units_json) {
    for (json::iterator it = attacking_units_json.begin(); it != attacking_units_json.end(); ++it) {
        UnitConfig* unitConfig = new UnitConfig();
        unitConfig->name = it.key();
        unitConfig->range = it.value().at("range");
        unitConfig->speed = it.value().at("speed");
        unitConfig->training_time = it.value().at("training_time");
        unitConfig->cost = it.value().at("cost");
        unitConfig->health = it.value().at("health");
        unitConfig->weapon = it.value().at("weapon");
        unitConfig->pixelSize = {32, 32};
        unitsConfig[it.key()] = unitConfig;
    }
}

void GameConfiguration::parseCosechadoraConfig(json& cosechadora_json) {
    UnitConfig* cosechadoraConfig = new UnitConfig();
    cosechadoraConfig->speed = cosechadora_json.at("speed");
    cosechadoraConfig->training_time = cosechadora_json.at("training_time");
    cosechadoraConfig->cost = cosechadora_json.at("cost");
    cosechadoraConfig->health = cosechadora_json.at("health");
    cosechadoraConfig->pixelSize = {32, 32};
    unitsConfig[HARVESTER] = cosechadoraConfig;
}

void GameConfiguration::parseBuildingsConfig(json& buildings_json) {
    for (json::iterator it = buildings_json.begin(); it != buildings_json.end(); ++it) {
        BuildingConfig* buildingConfig = new BuildingConfig();
        buildingConfig->name = it.key();
        buildingConfig->energy = it.value().at("energy");
        buildingConfig->cost = it.value().at("cost");
        buildingConfig->tileSize = it.value().at("size");
        buildingConfig->health = it.value().at("health");
        buildingConfig->capacity = it.value().at("capacity");
        buildingsConfig[it.key()] = buildingConfig;
    }
}

void GameConfiguration::parseGameConfiguration(json &configuration_json) {
	for (json::iterator it = configuration_json.begin(); it != configuration_json.end(); ++it) {
		if (it.key() == CONFIGURATION_WEAPONS_KEY) {
			parseWeapons(it.value());
		} else if (it.key() == CONFIGURATION_SOLDIERS_KEY) {
            parseAttackingUnitsConfig(it.value());
        } else if (it.key() == CONFIGURATION_HARVESTER_KEY) {
            parseCosechadoraConfig(it.value());
        } else if (it.key() == CONFIGURATION_BUILDINGS_KEY) {
            parseBuildingsConfig(it.value());
        }
	}
}

GameConfiguration::GameConfiguration(const std::string& config_file_path) {
	json game_items_configuration = json_utils::parseAsJson(config_file_path);
	parseGameConfiguration(game_items_configuration);
}

std::vector<std::string> GameConfiguration::getAvailableObjectsFor(const Player& player) const {
    std::vector<std::string> availableObjects;
    for (const auto& building : buildingsConfig) {
        if (building.first == CONSTRUCTION_CENTER) continue;
        if (building.second->cost <= player.especia && building.second->energy <= player.energia) {
            availableObjects.push_back(building.first);
        }
    }
    std::vector<std::string> availableUnits;
    if (player.buildingsOwnedNames.find(BARRACKS) != player.buildingsOwnedNames.end()) {
        availableUnits.push_back(LIGHT_INFANTRY);
        availableUnits.push_back(HEAVY_INFANTRY);
    }
    if (player.buildingsOwnedNames.find(LIGHT_FACTORY) != player.buildingsOwnedNames.end()) {
        availableUnits.push_back(TRIKE);
        availableUnits.push_back(RAIDER);
    }
    if (player.buildingsOwnedNames.find(HEAVY_FACTORY) != player.buildingsOwnedNames.end()) {
        availableUnits.push_back(TANK);
        availableUnits.push_back(HARVESTER);
    }
    for (const auto& unit_name : availableUnits) {
        if (unitsConfig.at(unit_name)->cost <= player.especia) {
            availableObjects.push_back(unit_name);
        }
    }
    return availableObjects;
}

const std::map<std::string, std::vector<SpriteType>> OBJECT_SPRITES_MAP = {
    {CONSTRUCTION_CENTER, {SPRITE_CONSTRUCTION_CENTER}},
    {WIND_TRAPS, {SPRITE_WIND_TRAPS}},
    {REFINERY, {SPRITE_REFINERY}},
    {BARRACKS, {
        SPRITE_ATREIDES_BARRACKS, 
        SPRITE_HARKUNNAN_BARRACKS, 
        SPRITE_ORDOS_BARRACKS
        }
    },
    {LIGHT_FACTORY, {SPRITE_LIGHT_FACTORY}},
    {HEAVY_FACTORY, {SPRITE_HEAVY_FACTORY}},
    {SILO, {SPRITE_SILO}},
    {TRIKE, {SPRITE_TRIKE}},
    {RAIDER, {SPRITE_RAIDER}},
    {TANK, {SPRITE_TANK}},
    {HARVESTER, {SPRITE_HARVESTER}},
    {LIGHT_INFANTRY, {SPRITE_LIGHT_INFANTRY}},
    {HEAVY_INFANTRY, {SPRITE_HEAVY_INFANTRY}}
};

std::pair<int, int> GameConfiguration::getBuildingCost(const std::string& buildingName) const {
    return {buildingsConfig.at(buildingName)->cost, buildingsConfig.at(buildingName)->energy};
}

#define TIEMPO_CONSTRUCCION_EDIFICIOS 5

int GameConfiguration::getTiempoBuilding(const std::string& buildingName) const {
    return TIEMPO_CONSTRUCCION_EDIFICIOS;
}

Building* GameConfiguration::getBuilding(Player& player, int id, const std::string& buildingName) const {
    const BuildingConfig* config = buildingsConfig.at(CONSTRUCTION_CENTER);
    Point pixelSize = {config->tileSize.row * TILE_PIXEL_RATE, config->tileSize.col * TILE_PIXEL_RATE};
    return new Building(player, id, buildingName, config->health, pixelSize);
}

int GameConfiguration::getUnitCost(const std::string& unitName) const {
    return unitsConfig.at(unitName)->cost;
}

int GameConfiguration::getTiempoUnit(const std::string& unitName) const {
    return unitsConfig.at(unitName)->training_time;
}

Infanteria* GameConfiguration::getInfanteria(Player& player, int id, const Point& initialPos, Map& map, const std::string& unitName) const {
    const UnitConfig* config = unitsConfig.at(unitName);
    return new Infanteria(player, id, unitName, config->health, config->pixelSize, initialPos, map, config->speed, *weapons.at(config->weapon), config->range);
}

Vehiculo* GameConfiguration::getVehiculo(Player& player, int id, const Point& initialPos, Map& map, const std::string& unitName) const {
    const UnitConfig* config = unitsConfig.at(unitName);
    return new Vehiculo(player, id, unitName, config->health, config->pixelSize, initialPos, map, config->speed, *weapons.at(config->weapon), config->range);
}

Cosechadora* GameConfiguration::getCosechadora(Player& player, int id, const Point& initialPos, Map& map) const {
    const UnitConfig* config = unitsConfig.at(HARVESTER);
    return new Cosechadora(player, id, HARVESTER, config->health, config->pixelSize, initialPos, map, config->speed);
}

std::string GameConfiguration::getCreationBuildingFor(const std::string& unitName) const {
    if (unitName == LIGHT_INFANTRY || unitName == HEAVY_INFANTRY) return BARRACKS;
    if (unitName == TRIKE || unitName == RAIDER) return LIGHT_FACTORY;
    if (unitName == TANK || unitName == HARVESTER) return HEAVY_FACTORY;
}

GameConfiguration::~GameConfiguration() {
    for (auto& weapon : weapons) {
        delete weapon.second;
    }
    for (auto& unitConfig : unitsConfig) {
        delete unitConfig.second;
    }
    for (auto& buildingConfig : buildingsConfig) {
        delete buildingConfig.second;
    }
}
