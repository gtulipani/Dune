#include "Event.h"

Event::Event(string type, Point src, Point dst) : type(move(type)), src(move(src)), dst(move(dst)) {}

Event::Event(const Event &other) : Event(
        other.type,
        other.src,
        other.dst) {}

Event::Event(Event &&other) noexcept : Event(
        move(other.type),
        move(other.src),
        move(other.dst)) {}

Event &Event::operator=(const Event &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = other.type;
    this->src = other.type;
    this->dst = other.dst;

    return *this;
}

Event &Event::operator=(Event &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = move(other.type);
    this->src = move(other.src);
    this->dst = move(other.dst);

    return *this;
}

Point& Event::getSource() {
    return src;
}

Point& Event::getDestiny() {
    return dst;
}
