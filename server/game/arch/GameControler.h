#ifndef __GAME_CONTROLER__
#define __GAME_CONTROLER__

#include <vector>
#include <map>

#include <Sprites.h>

#include "GameConfiguration.h"

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
    std::map<int, SelectableGameObject*> gameObjects;
    std::map<int, Player*> players;
    std::map<int, InProgressGameObject*> inProgressUnits;
    std::map<int, InProgressGameObject*> inProgressBuildings;

    void initializePlayers(int number_of_player);

    public:
    explicit GameControler(Map& map, const GameConfiguration& gameConfig);

    void initialize(int number_of_players);

    void tick();

    std::vector<Picturable> getStateFor(int player_id);

    void leftClick(int player_id, const Point& point);

    void rightClick(int player_id, const Point& point);

    void createTrike(int player_id);

    void createBuilding(int player_id, const Sprites& sprite);

    void locateBuildingAt(int id, const Point& pos);

    void createCosechadora(int player_id);

    void updateGameObjects();

    ~GameControler();
};

#endif // __GAME_CONTROLER__
