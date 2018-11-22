#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>

class Building;
class SelectableGameObject;

struct Player {
    const int id;
    std::vector<SelectableGameObject*> selectedObjects = {};
    unsigned int especia = 1000;
    
    Player(unsigned int id);

    void addEspecia(unsigned int newEspecia);
};

#endif
