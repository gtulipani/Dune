#include "GameStatusEvent.h"

GameStatusEvent::GameStatusEvent(const GameStatusEvent &other) {
    this->especia = other.especia;
    this->energy = other.energy;
    this->picturables = other.picturables;
    this->availableObjects = other.availableObjects;
}

GameStatusEvent::GameStatusEvent(GameStatusEvent &&other) noexcept {
    this->especia = other.especia;
    this->energy = other.energy;
    this->picturables = std::move(other.picturables);
    this->availableObjects = std::move(other.availableObjects);

    other.especia = 0;
    other.energy = 0;
}

GameStatusEvent &GameStatusEvent::operator=(const GameStatusEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->especia = other.especia;
    this->energy = other.energy;
    this->picturables = other.picturables;
    this->availableObjects = other.availableObjects;

    return *this;
}

GameStatusEvent &GameStatusEvent::operator=(GameStatusEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->especia = other.especia;
    this->energy = other.energy;
    this->picturables = std::move(other.picturables);
    this->availableObjects = std::move(other.availableObjects);

    other.especia = 0;
    other.energy = 0;

    return *this;
}
