#include "Picturable.h"

Picturable::Picturable(int id, std::string type, bool selected, Point position, int life, int motion) :
    id(id),
    type(std::move(type)),
    selected(selected),
    position(std::move(position)),
    life(life),
    motion(motion) {}

Picturable::Picturable(const Picturable &other) : Picturable(
        other.id,
        other.type,
        other.selected,
        other.position,
        other.life,
        other.motion) {}

Picturable::Picturable(Picturable &&other) noexcept : Picturable(
        other.id,
        std::move(other.type),
        other.selected,
        std::move(other.position),
        other.life,
        other.motion) {
    other.id = 0;
    other.selected = false;
    other.life = 0;
    other.motion = 0;
}

Picturable &Picturable::operator=(const Picturable &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->id = other.id;
    this->type = other.type;
    this->selected = other.selected;
    this->position = other.position;
    this->life = other.life;
    this->motion = other.motion;

    return *this;
}

Picturable &Picturable::operator=(Picturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->id = other.id;
    this->type = other.type;
    this->selected = other.selected;
    this->position = other.position;
    this->life = other.life;
    this->motion = other.motion;

    other.id = 0;
    other.selected = false;
    other.life = 0;
    other.motion = 0;

    return *this;
}
