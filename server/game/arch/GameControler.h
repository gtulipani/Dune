#ifndef __GAME_CONTROLER__
#define __GAME_CONTROLER__

#include <vector>
#include <map>

#include <Sprites.h>

class SelectableGameObject;
class InProgressGameObject;
class Map;
class Point;
class Picturable;
class Player;
class Especia;

class GameControler {
    private:
    unsigned int next_id = 0;
    Map& map;
    std::map<unsigned int, Especia*> especias;
    std::map<unsigned int, SelectableGameObject*> gameObjects;
    std::map<unsigned int, Player*> players;
    std::map<unsigned int, InProgressGameObject*> inProgressUnits;
    std::map<unsigned int, InProgressGameObject*> inProgressBuildings;

    void initializePlayers(unsigned int number_of_player);

    public:
    explicit GameControler(Map& map);

    void initialize(unsigned int number_of_players);

    void tick();

    std::vector<Picturable> getStates();

    void leftClick(unsigned int player_id, const Point& point);

    void rightClick(unsigned int player_id, const Point& point);

    void createTrike(unsigned int player_id);

    void createBuilding(unsigned int player_id, const Sprites& sprite);

    void locateBuildingAt(unsigned int id, const Point& pos);

    void createCosechadora(unsigned int player_id);

    void updateGameObjects();

    ~GameControler();
};

#endif // __GAME_CONTROLER__
