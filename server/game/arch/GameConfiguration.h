#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

#include <map>
#include <string>
#include "../model/Weapon.h"
#include "Sprites.h"
#include <Point.h>

using json = nlohmann::json;

class Infanteria;
class Vehiculo;
class Cosechadora;
class Point;
class Map;
class Player;
class Building;

struct UnitConfig {
    std::string name;
    int range;
    int speed;
    int training_time;
    int cost;
    int health;
    Point pixelSize;
    std::string weapon;
};

struct BuildingConfig {
    std::string name;
    int energy;
    int cost;
    Point tileSize;
    int health;
    int capacity;
};

class GameConfiguration {
    private:
    std::map<std::string, UnitConfig*> unitsConfig;
    std::map<std::string, Weapon*> weapons;
    std::map<std::string, BuildingConfig*> buildingsConfig;

    void parseWeapons(json& weapons_json);

    void parseAttackingUnitsConfig(json& attacking_units_json);

    void parseCosechadoraConfig(json& cosechadora_json);

    void parseBuildingsConfig(json& buildings_json);

    void parseGameConfiguration(json& game_items_configuration);

    public:
    GameConfiguration(const std::string& config_file_path);

    std::vector<std::string> getAvailableObjectsFor(const Player& player) const;

    int getTiempoBuilding(const std::string& buildingName) const;

    Building* getBuilding(Player& player, int id, const Point& initialPos, const std::string& buildingName) const;

    int getTiempoUnit(const std::string& unitName) const;

    Infanteria* getInfanteria(Player& player, int id, const Point& initialPos, Map& map, const std::string& unitName) const;

    Vehiculo* getVehiculo(Player& player, int id, const Point& initialPos, Map& map, const std::string& unitName) const;

    Cosechadora* getCosechadora(Player& player, int id, const Point& intialPos, Map& map) const;

    ~GameConfiguration();
};

#endif
