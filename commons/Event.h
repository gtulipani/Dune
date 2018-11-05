#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>
#include "Point.h"
#include "json.hpp"

#ifndef __EVENT_TYPES__
#define __EVENT_TYPES__
// Define the types of events
#define TERRAIN_SIZE "TERRAIN_SIZE"
#define TERRAIN_EVENT "TERRAIN"
#define TERRAIN_FINISHED_EVENT "TERRAIN_FINISHED"
#define MOVEMENT_EVENT "MOVEMENT"
#define CONNECTION_SUCCESS_EVENT "CONNECTION_SUCCESS"
#define GAME_STARTED_EVENT "GAME_STARTED"

#endif

using namespace std;
using json = nlohmann::json;

struct Event {
public:
    int id{};
    string type;
    Point dst;

    Event() = default;

    explicit Event(string type);

    Event(int id, string type);

    Event(string type, Point dst);

    Event(int id, string type, Point dst);

    Event(const Event &other);

    Event(Event &&other) noexcept;

    // Overloading the assignment by copy
    Event &operator=(const Event &other);

    // Overloading the assignment by movement
    Event &operator=(Event &&other) noexcept;

    Point& getDestiny();
};


#endif //__EVENT_H__
