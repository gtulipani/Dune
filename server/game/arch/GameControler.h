#ifndef __GAME_CONTROLER__
#define __GAME_CONTROLER__

#include <vector>
#include <map>

#include <Sprites.h>

#include "GameConfiguration.h"

class GameStatusEvent;
class SelectableGameObject;
class InProgressGameObject;
class Map;
class Point;
class Picturable;
class Player;
class Especia;

class GameControler {
    private:
    int next_id = 0;
    Map& map;
    const GameConfiguration& gameConfig;
    std::map<int, Especia*> especias;
    std::map<int, Player*> players;

    void initializePlayers(int number_of_player);

    public:
    explicit GameControler(Map& map, const GameConfiguration& gameConfig);

    void initialize(int number_of_players);

    void processLostPlayer(int player_id);

    void tick();

    std::pair<GameStatusEvent, bool> getStateFor(int player_id) const;

    void leftClick(int player_id, const Point& a, const Point& b);

    void rightClick(int player_id, const Point& point);

    void createVehiculo(int player_id, const std::string& unitName);

    void createInfanteria(int player_id, const std::string& unitName);

    void createBuilding(int player_id, const std::string& buildingName);

    void locateBuildingAt(int player_id, int building_id, const Point& pos);

    void createCosechadora(int player_id);

    void updateGameObjects();

    ~GameControler();
};

#endif // __GAME_CONTROLER__
