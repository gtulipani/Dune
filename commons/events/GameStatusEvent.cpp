#include "GameStatusEvent.h"

GameStatusEvent::GameStatusEvent(const GameStatusEvent &other) {
    this->especia = other.especia;
    this->energia = other.energia;
    this->picturables = other.picturables;
    this->selectedObjects = other.selectedObjects;
    this->availableObjects = other.availableObjects;
}

GameStatusEvent::GameStatusEvent(GameStatusEvent &&other) noexcept {
    this->especia = other.especia;
    this->energia = other.energia;
    this->picturables = std::move(other.picturables);
    this->selectedObjects = std::move(other.selectedObjects);
    this->availableObjects = std::move(other.availableObjects);

    other.especia = 0;
    other.energia = 0;
}

GameStatusEvent &GameStatusEvent::operator=(const GameStatusEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->especia = other.especia;
    this->energia = other.energia;
    this->picturables = other.picturables;
    this->selectedObjects = other.selectedObjects;
    this->availableObjects = other.availableObjects;

    return *this;
}

GameStatusEvent &GameStatusEvent::operator=(GameStatusEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->especia = other.especia;
    this->energia = other.energia;
    this->picturables = std::move(other.picturables);
    this->selectedObjects = std::move(other.selectedObjects);
    this->availableObjects = std::move(other.availableObjects);

    other.especia = 0;
    other.energia = 0;

    return *this;
}
