#ifndef __GAME_CONTROLER__
#define __GAME_CONTROLER__

#include <vector>

class GameObject;
class Map;
class Point;

class GameControler {
    private:
    unsigned int next_id = 0;
    std::vector<GameObject*>& gameObjects;
    Map& map;
    GameObject* selectedObject = nullptr;

    public:
    explicit GameControler(std::vector<GameObject*>& _gameObjects, Map& _map);

    void initializeMap();

    void leftClick(const Point& point);

    void rightClick(const Point& point);

    void createWalkingUnit(const Point& point);

    void createCosechadora(const Point& point);

    void updateGameObjects();
};

#endif // __GAME_CONTROLER__
