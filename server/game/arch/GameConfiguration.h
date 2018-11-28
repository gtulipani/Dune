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

struct AttackingUnitConfig {
    std::string name;
    int range;
    int speed;
    int training_time;
    int cost;
    int health;
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
    std::map<std::string, AttackingUnitConfig*> attackingUnitsConfig;
    std::map<std::string, Weapon*> weapons;
    std::map<std::string, BuildingConfig*> buildingsConfig;

    void parseWeapons(json& weapons_json);

    void parseAttackingUnitsConfig(json& attacking_units_json);

    void parseCosechadoraConfig(json& cosechadora_json);

    void parseBuildingsConfig(json& buildings_json);

    void parseGameConfiguration(json& game_items_configuration);

    Infanteria* infanteria(Player& player, int id, const Point& initialPixelPosition, Map& map, const AttackingUnitConfig* config, Type type, const Point& size) const;

    Vehiculo* vehiculo(Player& player, int id, const Point& initialPixelPosition, Map& map, const AttackingUnitConfig* config, Type type, const Point& size) const;

    public:
    GameConfiguration(const std::string& config_file_path);

    Infanteria* getInfanteriaLigera(Player& player, int id, const Point& initialPos, Map& map) const;

    int getTiempoInfanteriaLigera() const;

    Infanteria* getInfanteriaPesada(Player& player, int id, const Point& initialPos, Map& map) const;

    int getTiempoInfanteriaPesada() const;

    Vehiculo* getTrike(Player& player, int id, const Point& initialPos, Map& map) const;

    int getTiempoTrike() const;

    Vehiculo* getRaider(Player& player, int id, const Point& initialPos, Map& map) const;

    int getTiempoRaider() const;

    Vehiculo* getTanque(Player& player, int id, const Point& initialPos, Map& map) const;

    int getTiempoTanque() const;

    Cosechadora* getCosechadora(Player& player, int id, const Point& initialPos, Map& map) const;

    int getTiempoCosechadora() const;

    int getTiempoEdificio() const;

    Building* getCentroConstruccion(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getFabricaLigera(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getTrampasAire(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getFabricaPesada(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getRefineria(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getSilo(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getCuartel(Player& player, int id, const Point& initialPos, Map& map) const;

    Building* getPalacio(Player& player, int id, const Point& initialPos, Map& map) const;

    ~GameConfiguration();
};

#endif
