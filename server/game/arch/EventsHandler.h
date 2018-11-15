#ifndef __EVENTS_HANDLER_H__
#define __EVENTS_HANDLER_H__

#include <list>

class GameObject;
class Map;
class Point;

class EventsHandler {
    private:
    std::list<GameObject*>& gameObjects;
    Map& map;
    GameObject* selectedObject = nullptr;

    public:
    explicit EventsHandler(std::list<GameObject*>& _gameObjects, Map& _map);

    void leftClick(const Point& point);

    void rightClick(const Point& point);

    void createWalkingUnit(const Point& point);
};

#endif
