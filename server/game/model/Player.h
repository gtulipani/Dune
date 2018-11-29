#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <map>
#include <set>

class SelectableGameObject;
class WalkingUnit;
class AttackingUnit;
class Building;
class InProgressGameObject;

struct Player {
    const int id;
    std::map<int, SelectableGameObject*> selectedObjects{};
    std::map<int, WalkingUnit*> units{};
    std::map<int, Building*> buildings{};
    std::map<int, InProgressGameObject*> inProgressUnits;
    std::map<int, InProgressGameObject*> inProgressBuildings;
    std::set<std::string> buildingsOwnedNames{};
    int especia = 1000;
    int energia = 0;
    bool changedSelection = false;
    bool lost = false;
    
    Player(int id);

    void addEspecia(int newEspecia);

    bool operator==(const Player& other) const;
};

#endif
