#ifndef __GAME_CONTROLER__
#define __GAME_CONTROLER__

#include <list>

class GameObject;
class Map;
class Point;

class GameControler {
    private:
    std::list<GameObject*>& gameObjects;
    Map& map;
    GameObject* selectedObject = nullptr;

    public:
    explicit GameControler(std::list<GameObject*>& _gameObjects, Map& _map);

    void initializeMap();

    void leftClick(const Point& point);

    void rightClick(const Point& point);

    void createWalkingUnit(const Point& point);

    void createCosechadora(const Point& point);
};

#endif // __GAME_CONTROLER__
