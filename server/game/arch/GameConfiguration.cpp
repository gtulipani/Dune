#include "GameConfiguration.h"

#include <json/json.hpp>
#include <json/JSONUtils.h>

#include "../model/Infanteria.h"
#include "../model/Vehiculo.h"
#include "../model/Cosechadora.h"
#include "../model/Building.h"

#include "TileUtils.h"

#include "Sprites.h"

#define CONFIGURATION_BUILDINGS_KEY "buildings"
#define CONFIGURATION_WEAPONS_KEY "weapons"
#define CONFIGURATION_SOLDIERS_KEY "attacking_units"
#define CONFIGURATION_COSECHADORA_KEY "cosechadora"

void GameConfiguration::parseWeapons(json& weapons_json) {
    for (json::iterator it = weapons_json.begin(); it != weapons_json.end(); ++it) {
        Weapon* weapon = new Weapon(it.key(), it.value().at("damage"), it.value().at("shot_frequency"));
        weapons[it.key()] = weapon;
    }
}

void GameConfiguration::parseAttackingUnitsConfig(json& attacking_units_json) {
    for (json::iterator it = attacking_units_json.begin(); it != attacking_units_json.end(); ++it) {
        AttackingUnitConfig* attackingUnitConfig = new AttackingUnitConfig();
        attackingUnitConfig->name = it.key();
        attackingUnitConfig->range = it.value().at("range");
        attackingUnitConfig->speed = it.value().at("speed");
        attackingUnitConfig->training_time = it.value().at("training_time");
        attackingUnitConfig->cost = it.value().at("cost");
        attackingUnitConfig->health = it.value().at("health");
        attackingUnitConfig->weapon = it.value().at("armamento");
        attackingUnitsConfig[it.key()] = attackingUnitConfig;
    }
}

void GameConfiguration::parseCosechadoraConfig(json& cosechadora_json) {
    AttackingUnitConfig* cosechadoraConfig = new AttackingUnitConfig();
    cosechadoraConfig->speed = cosechadora_json.at("speed");
    cosechadoraConfig->training_time = cosechadora_json.at("training_time");
    cosechadoraConfig->cost = cosechadora_json.at("cost");
    cosechadoraConfig->health = cosechadora_json.at("health");
    attackingUnitsConfig["cosechadora"] = cosechadoraConfig;
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
        } else if (it.key() == CONFIGURATION_COSECHADORA_KEY) {
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

Infanteria* GameConfiguration::infanteria(Player& player, int id, const Point& initialPos, Map& map, const AttackingUnitConfig* config, Type type, const Point& size) const {
    return new Infanteria(player, id, type, config->health, size, initialPos, map, config->speed, *weapons.at(config->weapon), config->range);
}

Vehiculo* GameConfiguration::vehiculo(Player& player, int id, const Point& initialPos, Map& map, const AttackingUnitConfig* config, Type type, const Point& size) const {
    return new Vehiculo(player, id, type, config->health, size, initialPos, map, config->speed, *weapons.at(config->weapon), config->range);
}

Infanteria* GameConfiguration::getInfanteriaLigera(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("infanteria_ligera");
    return infanteria(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoInfanteriaLigera() const {
    return attackingUnitsConfig.at("infanteria_ligera")->training_time;
}

Infanteria* GameConfiguration::getInfanteriaPesada(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("infanteria_pesada");
    return infanteria(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoInfanteriaPesada() const {
    return attackingUnitsConfig.at("infanteria_pesada")->training_time;
}

Vehiculo* GameConfiguration::getTrike(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("trike");
    return vehiculo(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoTrike() const {
    return attackingUnitsConfig.at("trike")->training_time;
}

Vehiculo* GameConfiguration::getRaider(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("raider");
    return vehiculo(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoRaider() const {
    return attackingUnitsConfig.at("raider")->training_time;
}

Vehiculo* GameConfiguration::getTanque(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("tanque");
    return vehiculo(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoTanque() const {
    return attackingUnitsConfig.at("tanque")->training_time;
}

Cosechadora* GameConfiguration::getCosechadora(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("cosechadora");
    return new Cosechadora(player, id, HARVESTER, config->health, {32, 32}, initialPos, map, config->speed);
}

int GameConfiguration::getTiempoCosechadora() const {
    return attackingUnitsConfig.at("cosechadora")->training_time;
}

#define TIEMPO_CONSTRUCCION_EDIFICIOS 5

int GameConfiguration::getTiempoEdificio() const {
    return TIEMPO_CONSTRUCCION_EDIFICIOS;
}

Building* GameConfiguration::getCentroConstruccion(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("centro_construccion");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getFabricaLigera(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("fabrica_ligera");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getTrampasAire(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("trampas_aire");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getFabricaPesada(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("fabrica_pesada");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getRefineria(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("refineria");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getSilo(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("silo");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getCuartel(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("cuartel");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

Building* GameConfiguration::getPalacio(Player& player, int id, const Point& initialPos, Map& map) const {
    const BuildingConfig* config = buildingsConfig.at("palacio");
    return new Building(player, id, CONSTRUCTION_CENTER, config->health, {config->tileSize.row * TILE_PIXEL_RATE, 96}, initialPos);
}

GameConfiguration::~GameConfiguration() {
    for (auto weapon : weapons) {
        delete weapon.second;
    }
    for (auto attackingUnitConfig : attackingUnitsConfig) {
        delete attackingUnitConfig.second;
    }
}
