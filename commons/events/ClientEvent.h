#ifndef __CLIENT_EVENT_H__
#define __CLIENT_EVENT_H__

#include <string>
#include "../Point.h"
#include "../json/json.hpp"

using namespace std;
using json = nlohmann::json;

struct ClientEvent {
public:
    int player_id{};
    string type;
    Point position;

    ClientEvent() = default;

    ClientEvent(int id, string type, Point dst);

    ClientEvent(const ClientEvent &other);

    ClientEvent(ClientEvent &&other) noexcept;

    // Overloading the assignment by copy
    ClientEvent &operator=(const ClientEvent &other);

    // Overloading the assignment by movement
    ClientEvent &operator=(ClientEvent &&other) noexcept;
};


#endif //__CLIENT_EVENT_H__
