#include "GameStatusEvent.h"

GameStatusEvent::GameStatusEvent(std::vector<Picturable> picturables) :
        picturables(std::move(picturables)) {}

GameStatusEvent::GameStatusEvent(const GameStatusEvent &other) : GameStatusEvent(
        other.picturables) {}

GameStatusEvent::GameStatusEvent(GameStatusEvent &&other) noexcept : GameStatusEvent(
        std::move(other.picturables)) {}

GameStatusEvent &GameStatusEvent::operator=(const GameStatusEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturables = other.picturables;

    return *this;
}

GameStatusEvent &GameStatusEvent::operator=(GameStatusEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->picturables = std::move(other.picturables);

    return *this;
}
