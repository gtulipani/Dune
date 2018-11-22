#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <map>

class Building;
class SelectableGameObject;

struct Player {
    const int id;
    std::map<unsigned int, SelectableGameObject*> selectedObjects = {};
    unsigned int especia = 1000;
    bool changedSelection = false;
    
    Player(unsigned int id);

    void addEspecia(unsigned int newEspecia);

    bool operator==(const Player& other) const;
};

#endif
