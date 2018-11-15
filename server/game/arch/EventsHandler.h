#ifndef __EVENTS_HANDLER_H__
#define __EVENTS_HANDLER_H__

#include <list>

class GameObject;
class Terrain;
class Point;

class EventsHandler {
    private:
    std::list<GameObject*>& gameObjects;
    Terrain& terrain;
    GameObject* selectedObject = nullptr;

    public:
    explicit EventsHandler(std::list<GameObject*>& _gameObjects, Terrain& _terrain);

    void leftClick(const Point& point);

    void rightClick(const Point& point);

    void createWalkingUnit(const Point& point);
};

#endif
