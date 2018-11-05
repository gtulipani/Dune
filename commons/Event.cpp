#include "Event.h"

#define DEFAULT_ID 0
#define DEFAULT_POINT Point(0,0)

Event::Event(int id, string type, Point dst) :
        id(id),
        type(move(type)),
        dst(move(dst)) {}

Event::Event(string type, Point dst) : Event(
        DEFAULT_ID,
        move(type),
        move(dst)) {}

Event::Event(int id, string type) : Event(id, move(type), DEFAULT_POINT) {}

Event::Event(string type) : Event(DEFAULT_ID, move(type)) {}

Event::Event(const Event &other) : Event(
        other.id,
        other.type,
        other.dst) {}

Event::Event(Event &&other) noexcept : Event(
        other.id,
        move(other.type),
        move(other.dst)) {
    other.id = 0;
}

Event &Event::operator=(const Event &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = other.type;
    this->id = other.id;
    this->dst = other.dst;

    return *this;
}

Event &Event::operator=(Event &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = move(other.type);
    this->id = other.id;
    this->dst = move(other.dst);

    other.id = 0;

    return *this;
}

Point& Event::getDestiny() {
    return dst;
}
