#ifndef __GAME_STATUS_EVENT_H__
#define __GAME_STATUS_EVENT_H__

#include <vector>
#include "../Picturable.h"

struct GameStatusEvent {
public:
    std::vector<Picturable> picturables;

    GameStatusEvent() = default;

    explicit GameStatusEvent(std::vector<Picturable> matrix);

    GameStatusEvent(const GameStatusEvent &other);

    GameStatusEvent(GameStatusEvent &&other) noexcept;

    // Overloading the assignment by copy
    GameStatusEvent &operator=(const GameStatusEvent &other);

    // Overloading the assignment by movement
    GameStatusEvent &operator=(GameStatusEvent &&other) noexcept;
};


#endif //__GAME_STATUS_EVENT_H__
