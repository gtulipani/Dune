#ifndef __GAME_CONFIGURATION_H__
#define __GAME_CONFIGURATION_H__

#include <map>
#include <string>
#include "../model/Weapon.h"
#include "Sprites.h"

using json = nlohmann::json;

class Infanteria;
class Vehiculo;
class Cosechadora;
class Point;
class Map;
class Player;

struct AttackingUnitConfig {
    int range;
    int speed;
    int training_time;
    int cost;
    int health;
    std::string weapon;
};

class GameConfiguration {
    private:
    std::map<std::string, AttackingUnitConfig*> attackingUnitsConfig;
    std::map<std::string, Weapon*> weapons;

    void parseWeapons(json& weapons_json);

    void parseAttackingUnitsConfig(json& attacking_unit_json);

    void parseCosechadoraConfig(json& cosechadora_json);

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

    ~GameConfiguration();
};

#endif
