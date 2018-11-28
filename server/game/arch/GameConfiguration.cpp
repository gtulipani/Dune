#include "GameConfiguration.h"

#include <json/json.hpp>
#include <json/JSONUtils.h>

#include "../model/Infanteria.h"
#include "../model/Vehiculo.h"
#include "../model/Cosechadora.h"

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

void GameConfiguration::parseAttackingUnitsConfig(json& attacking_unit_json) {
    for (json::iterator it = attacking_unit_json.begin(); it != attacking_unit_json.end(); ++it) {
        AttackingUnitConfig* attackingUnitConfig = new AttackingUnitConfig();
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

void GameConfiguration::parseGameConfiguration(json &configuration_json) {
	for (json::iterator it = configuration_json.begin(); it != configuration_json.end(); ++it) {
		if (it.key() == CONFIGURATION_WEAPONS_KEY) {
			parseWeapons(it.value());
		} else if (it.key() == CONFIGURATION_SOLDIERS_KEY) {
            parseAttackingUnitsConfig(it.value());
        } else if (it.key() == CONFIGURATION_COSECHADORA_KEY) {
            parseCosechadoraConfig(it.value());
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
    return attackingUnitsConfig.at("infanteria_ligera")->cost;
}

Infanteria* GameConfiguration::getInfanteriaPesada(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("infanteria_pesada");
    return infanteria(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoInfanteriaPesada() const {
    return attackingUnitsConfig.at("infanteria_pesada")->cost;
}

Vehiculo* GameConfiguration::getTrike(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("trike");
    return vehiculo(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoTrike() const {
    return attackingUnitsConfig.at("trike")->cost;
}

Vehiculo* GameConfiguration::getRaider(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("raider");
    return vehiculo(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoRaider() const {
    return attackingUnitsConfig.at("raider")->cost;
}

Vehiculo* GameConfiguration::getTanque(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("tanque");
    return vehiculo(player, id, initialPos, map, config, TRIKE, {32, 32});
}

int GameConfiguration::getTiempoTanque() const {
    return attackingUnitsConfig.at("tanque")->cost;
}

Cosechadora* GameConfiguration::getCosechadora(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("cosechadora");
    return new Cosechadora(player, id, HARVESTER, config->health, {32, 32}, initialPos, map, config->speed);
}

int GameConfiguration::getTiempoCosechadora() const {
    return attackingUnitsConfig.at("cosechadora")->cost;
}

GameConfiguration::~GameConfiguration() {
    for (auto weapon : weapons) {
        delete weapon.second;
    }
    for (auto attackingUnitConfig : attackingUnitsConfig) {
        delete attackingUnitConfig.second;
    }
}
