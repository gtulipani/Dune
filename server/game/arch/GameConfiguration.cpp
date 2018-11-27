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
	for (map<string, json> weapon_fields : weapons_json) {
		for (auto &kv : weapon_fields) {
            Weapon* weapon = new Weapon(kv.first, kv.second.at("damage"), kv.second.at("shot_frequency"));
			weapons[kv.first] = weapon;
		}
	}
}

void GameConfiguration::parseAttackingUnitsConfig(json& attacking_unit_json) {
    for (map<string, json> attacking_unit_fields : attacking_unit_json) {
		for (auto &kv : attacking_unit_fields) {
            AttackingUnitConfig* attackingUnitConfig = new AttackingUnitConfig();
            attackingUnitConfig->range = kv.second.at("range");
            attackingUnitConfig->speed = kv.second.at("speed");
            attackingUnitConfig->training_time = kv.second.at("training_time");
            attackingUnitConfig->cost = kv.second.at("cost");
            attackingUnitConfig->health = kv.second.at("health");
            attackingUnitConfig->weapon = kv.second.at("armamento");
			attackingUnitsConfig[kv.first] = attackingUnitConfig;
		}
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

Infanteria* GameConfiguration::infanteria(Player& player, int id, const Point& initialPos, Map& map, const AttackingUnitConfig* config, Sprites sprite, const Point& size) const {
    return new Infanteria(player, id, sprite, config->health, size, initialPos, map, config->speed, *weapons.at(config->weapon), config->range);
}

Vehiculo* GameConfiguration::vehiculo(Player& player, int id, const Point& initialPos, Map& map, const AttackingUnitConfig* config, Sprites sprite, const Point& size) const {
    return new Vehiculo(player, id, sprite, config->health, size, initialPos, map, config->speed, *weapons.at(config->weapon), config->range);
}

Infanteria* GameConfiguration::getInfanteriaLigera(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("infanteria_ligera");
    return infanteria(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoInfanteriaLigera() const {
    return attackingUnitsConfig.at("infanteria_ligera")->cost;
}

Infanteria* GameConfiguration::getFremen(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("fremen");
    return infanteria(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoFremen() const {
    return attackingUnitsConfig.at("fremen")->cost;
}

Infanteria* GameConfiguration::getInfanteriaPesada(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("infanteria_pesada");
    return infanteria(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoInfanteriaPesada() const {
    return attackingUnitsConfig.at("infanteria_pesada")->cost;
}

Infanteria* GameConfiguration::getSardaukar(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("sardukar");
    return infanteria(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoSardukar() const {
    return attackingUnitsConfig.at("sardukar")->cost;
}

Vehiculo* GameConfiguration::getTrike(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("trike");
    return vehiculo(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoTrike() const {
    return attackingUnitsConfig.at("trike")->cost;
}

Vehiculo* GameConfiguration::getTanqueSonico(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("tanque_sonico");
    return vehiculo(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoTanqueSonico() const {
    return attackingUnitsConfig.at("tanque_sonico")->cost;
}

Vehiculo* GameConfiguration::getRaider(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("raider");
    return vehiculo(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoRaider() const {
    return attackingUnitsConfig.at("raider")->cost;
}

Vehiculo* GameConfiguration::getDesviador(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("desviador");
    return vehiculo(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoDesviador() const {
    return attackingUnitsConfig.at("desviador")->cost;
}

Vehiculo* GameConfiguration::getTanque(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("tanque");
    return vehiculo(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoTanque() const {
    return attackingUnitsConfig.at("tanque")->cost;
}

Vehiculo* GameConfiguration::getDevastador(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("devastador");
    return vehiculo(player, id, initialPos, map, config, TRIKE_SPRITE_DOWN, {32, 32});
}

unsigned int GameConfiguration::getTiempoDevastador() const {
    return attackingUnitsConfig.at("devastador")->cost;
}

Cosechadora* GameConfiguration::getCosechadora(Player& player, int id, const Point& initialPos, Map& map) const {
    const AttackingUnitConfig* config = attackingUnitsConfig.at("cosechadora");
    return new Cosechadora(player, id, TRIKE_SPRITE_DOWN, config->health, {32, 32}, initialPos, map, config->speed);
}

unsigned int GameConfiguration::getTiempoCosechadora() const {
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
