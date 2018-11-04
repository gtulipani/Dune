#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>
#include "Point.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Event {
private:
    string type;
    Point src;
    Point dst;
public:
    Event(std::string type, Point src, Point dst);

    Event(const Event &other);

    Event(Event &&other) noexcept;

    // Overloading the assignment by copy
    Event &operator=(const Event &other);

    // Overloading the assignment by movement
    Event &operator=(Event &&other) noexcept;

    Point& getSource();
    Point& getDestiny();

    friend void to_json(json &j, const Event &b);
    friend void from_json(const json &j, Event &b);
};


#endif //__EVENT_H__
