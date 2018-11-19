#ifndef __GAME_CONTROLER__
#define __GAME_CONTROLER__

#include <vector>
#include <map>

#include "../model/Map.h"

class GameObject;
class Map;
class Point;
class Picturable;
class Player;

class GameControler {
    private:
    unsigned int next_id = 0;
    std::map<unsigned int, GameObject*> gameObjects;
    Map& map;
    std::vector<Player> players;
    std::vector<GameObject*> selectedObjects;

    public:
    explicit GameControler(Map& map);

    void initialize(unsigned int number_of_players);

    void tick();

    std::vector<Picturable> getStates();

    void leftClick(unsigned int player_id, const Point& point);

    void rightClick(unsigned int player_id, const Point& point);

    void createWalkingUnit(unsigned int player_id, const Point& point);

    void createCosechadora(unsigned int player_id, const Point& point);

    void createBuilding(unsigned int player_id);

    void putBuildingAt(unsigned int building_id, const Point& position);

    void updateGameObjects();
};

#endif // __GAME_CONTROLER__
