#ifndef __GAME_STATUS_EVENT_H__
#define __GAME_STATUS_EVENT_H__

#include <vector>
#include "../Picturable.h"

struct GameStatusEvent {
public:
    int especia;
    int energia;
    std::vector<Picturable> picturables;
    std::vector<Picturable> selectedObjects;
    std::vector<std::string> availableObjects;

    GameStatusEvent() = default;

    GameStatusEvent(const GameStatusEvent &other);

    GameStatusEvent(GameStatusEvent &&other) noexcept;

    // Overloading the assignment by copy
    GameStatusEvent &operator=(const GameStatusEvent &other);

    // Overloading the assignment by movement
    GameStatusEvent &operator=(GameStatusEvent &&other) noexcept;
};


#endif //__GAME_STATUS_EVENT_H__
