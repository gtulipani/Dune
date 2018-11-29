#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <map>

class Building;
class SelectableGameObject;

struct Player {
    const int id;
    std::map<int, SelectableGameObject*> selectedObjects = {};
    std::map<std::string, Building*> buildings {};
    int especia = 1000;
    int energia = 0;
    bool changedSelection = false;
    
    Player(int id);

    void addEspecia(int newEspecia);

    bool operator==(const Player& other) const;
};

#endif
