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
    unsigned int range;
    unsigned int speed;
    unsigned int training_time;
    unsigned int cost;
    unsigned int health;
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

    Infanteria* infanteria(Player& player, int id, const Point& initialPixelPosition, Map& map, const AttackingUnitConfig* config, Sprites sprite, const Point& size) const;

    Vehiculo* vehiculo(Player& player, int id, const Point& initialPixelPosition, Map& map, const AttackingUnitConfig* config, Sprites psrite, const Point& size) const;

    public:
    GameConfiguration(const std::string& config_file_path);

    Infanteria* getInfanteriaLigera(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoInfanteriaLigera() const;

    Infanteria* getFremen(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoFremen() const;

    Infanteria* getInfanteriaPesada(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoInfanteriaPesada() const;

    Infanteria* getSardaukar(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoSardukar() const;

    Vehiculo* getTrike(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoTrike() const;

    Vehiculo* getTanqueSonico(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoTanqueSonico() const;

    Vehiculo* getRaider(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoRaider() const;

    Vehiculo* getDesviador(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoDesviador() const;

    Vehiculo* getTanque(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoTanque() const;

    Vehiculo* getDevastador(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoDevastador() const;

    Cosechadora* getCosechadora(Player& player, int id, const Point& initialPos, Map& map) const;

    unsigned int getTiempoCosechadora() const;

    ~GameConfiguration();
};

#endif
