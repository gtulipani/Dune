#include "ClientEvent.h"

ClientEvent::ClientEvent(int id, string type, Point position) :
        player_id(id),
        type(move(type)),
        position(move(position)) {}

ClientEvent::ClientEvent(const ClientEvent &other) : ClientEvent(
        other.player_id,
        other.type,
        other.position) {}

ClientEvent::ClientEvent(ClientEvent &&other) noexcept : ClientEvent(
        other.player_id,
        move(other.type),
        move(other.position)) {
    other.player_id = 0;
}

ClientEvent &ClientEvent::operator=(const ClientEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = other.type;
    this->player_id = other.player_id;
    this->position = other.position;

    return *this;
}

ClientEvent &ClientEvent::operator=(ClientEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = move(other.type);
    this->player_id = other.player_id;
    this->position = move(other.position);

    other.player_id = 0;

    return *this;
}
