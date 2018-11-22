#ifndef __CLIENT_EVENT_H__
#define __CLIENT_EVENT_H__

#include <string>
#include "../Point.h"
#include "../json/json.hpp"

#define RIGHT_CLICK_TYPE "RIGHT_CLICK"
#define LEFT_CLICK_TYPE "LEFT_CLICK"

#define CREATE_TRIKE_TYPE "CREATE_TRIKE"

#define CREATE_BUILDING_WIND_TRAPS "CREATE_BUILDING_WIND_TRAPS"
#define CREATE_BUILDING_REFINERY "CREATE_BUILDING_REFINERY"
#define CREATE_BUILDING_ATREIDES_BARRACKS "CREATE_BUILDING_ATREIDES_BARRACKS"
#define CREATE_BUILDING_HARKUNNAN_BARRACKS "CREATE_BUILDING_HARKUNNAN_BARRACKS"
#define CREATE_BUILDING_ORDOS_BARRACKS "CREATE_BUILDING_ORDOS_BARRACKS"
#define CREATE_BUILDING_LIGHT_FACTORY "CREATE_BUILDING_LIGHT_FACTORY"
#define CREATE_BUILDING_HEAVY_FACTORY "CREATE_BUILDING_HEAVY_FACTORY"
#define CREATE_BUILDING_SILO "CREATE_BUILDING_SILO"
#define CREATE_BUILDING_PALACE "CREATE_BUILDING_PALACE"

#define CREATE_COSECHADORA_TYPE "CREATE_COSECHADORA"
#define LOCATE_BUILDING_TYPE "LOCATE_BUILDING"

using namespace std;
using json = nlohmann::json;

struct ClientEvent {
public:
    unsigned int player_id{};
    string type;
    Point click_position{};
    Point release_position{};

    ClientEvent() = default;

    ClientEvent(unsigned int player_id, string type, Point click_position, Point release_position);

    ClientEvent(const ClientEvent &other);

    ClientEvent(ClientEvent &&other) noexcept;

    // Overloading the assignment by copy
    ClientEvent &operator=(const ClientEvent &other);

    // Overloading the assignment by movement
    ClientEvent &operator=(ClientEvent &&other) noexcept;
};


#endif //__CLIENT_EVENT_H__
