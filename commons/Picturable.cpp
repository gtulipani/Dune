#include "Picturable.h"

Picturable::Picturable(int id, int type, int sprite, bool selected, Point position, int health) :
    id(id),
    type(type),
    sprite(sprite),
    selected(selected),
    position(std::move(position)),
    health(health) {}

Picturable::Picturable(const Picturable &other) : Picturable(
        other.id,
        other.type,
        other.sprite,
        other.selected,
        other.position,
        other.health) {}

Picturable::Picturable(Picturable &&other) noexcept : Picturable(
        other.id,
        other.type,
        other.sprite,
        other.selected,
        std::move(other.position),
        other.health) {
    other.id = 0;
    other.type = 0;
    other.sprite = 0;
    other.selected = false;
    other.health = 0;
}

Picturable &Picturable::operator=(const Picturable &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->id = other.id;
    this->type = other.type;
    this->sprite = other.sprite;
    this->selected = other.selected;
    this->position = other.position;
    this->health = other.health;
    return *this;
}

Picturable &Picturable::operator=(Picturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->id = other.id;
    this->type = other.type;
    this->sprite = other.sprite;
    this->selected = other.selected;
    this->position = other.position;
    this->health = other.health;

    other.id = 0;
    other.type = 0;
    other.sprite = 0;
    other.selected = false;
    other.health = 0;

    return *this;
}
