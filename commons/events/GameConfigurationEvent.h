#ifndef __MAP_CONFIGURATION_EVENT_H__
#define __MAP_CONFIGURATION_EVENT_H__

#include "../Matrix.h"

struct GameConfigurationEvent {
public:
    int player_id{};
    Matrix matrix{};

    GameConfigurationEvent() = default;

    GameConfigurationEvent(int player_id, Matrix matrix);

    GameConfigurationEvent(const GameConfigurationEvent &other);

    GameConfigurationEvent(GameConfigurationEvent &&other) noexcept;

    // Overloading the assignment by copy
    GameConfigurationEvent &operator=(const GameConfigurationEvent &other);

    // Overloading the assignment by movement
    GameConfigurationEvent &operator=(GameConfigurationEvent &&other) noexcept;
};


#endif //__MAP_CONFIGURATION_EVENT_H__
