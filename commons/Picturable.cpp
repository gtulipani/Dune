#include "Picturable.h"

Picturable::Picturable(int id, int sprite, bool selected, Point position, Point size, int health) :
    id(id),
    sprite(sprite),
    selected(selected),
    position(std::move(position)),
    size(std::move(size)),
    health(health) {}

Picturable::Picturable(const Picturable &other) : Picturable(
        other.id,
        other.sprite,
        other.selected,
        other.position,
        other.size,
        other.health) {}

Picturable::Picturable(Picturable &&other) noexcept : Picturable(
        other.id,
        other.sprite,
        other.selected,
        std::move(other.position),
        std::move(other.size),
        other.health) {
    other.id = 0;
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
    this->sprite = other.sprite;
    this->selected = other.selected;
    this->position = other.position;
    this->size = other.size;
    this->health = other.health;
    return *this;
}

Picturable &Picturable::operator=(Picturable &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->id = other.id;
    this->sprite = other.sprite;
    this->selected = other.selected;
    this->position = other.position;
    this->size = other.size;
    this->health = other.health;

    other.id = 0;
    other.sprite = 0;
    other.selected = false;
    other.health = 0;

    return *this;
}
