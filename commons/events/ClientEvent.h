#ifndef __CLIENT_EVENT_H__
#define __CLIENT_EVENT_H__

// STL Libraries
#include <string>

// Commons Libraries
#include "../Point.h"
#include "../json/json.hpp"

using namespace std;
using json = nlohmann::json;

typedef enum ClientEventType {
    RIGHT_CLICK_EVENT_TYPE = 0,
    LEFT_CLICK_EVENT_TYPE = 1,
    CREATE_WIND_TRAPS_TYPE = 2,
    CREATE_REFINERY_TYPE = 3,
    CREATE_BARRACKS_TYPE = 4,
    CREATE_LIGHT_FACTORY_TYPE = 5,
    CREATE_HEAVY_FACTORY_TYPE = 6,
    CREATE_SILO_TYPE = 7,
    CREATE_TRIKE_TYPE = 8,
    CREATE_HARVESTER_TYPE = 9,
    CREATE_RAIDER_TYPE = 10,
    CREATE_TANK_TYPE = 11,
    CREATE_LIGHT_INFANTRY_TYPE = 12,
    CREATE_HEAVY_INFANTRY_TYPE = 13,
    LOCATE_BUILDING_TYPE = 14,
    SELL_TYPE = 15,
    CREATE_CONSTRUCTION_CENTER = 16
} ClientEventType;

struct ClientEvent {
public:
    unsigned int player_id{};
    int type{};
    int picturable_id{};
    Point click_position{};
    Point release_position{};

    ClientEvent() = default;

    ClientEvent(unsigned int player_id, int client_type, int picturable_id, Point click_position, Point release_position);

    ClientEvent(const ClientEvent &other);

    ClientEvent(ClientEvent &&other) noexcept;

    // Overloading the assignment by copy
    ClientEvent &operator=(const ClientEvent &other);

    // Overloading the assignment by movement
    ClientEvent &operator=(ClientEvent &&other) noexcept;
};


#endif //__CLIENT_EVENT_H__
