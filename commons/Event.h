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
    Point& src;
    Point& dst;
public:
    Event(std::string type, Point& src, Point& dst);

    friend void to_json(json &j, const Event &b);
};


#endif //__EVENT_H__
