#include "ClientEvent.h"

ClientEvent::ClientEvent(unsigned int player_id, int client_type, vector<int> picturable_ids, Point click_position, Point release_position) :
        player_id(player_id),
        type(client_type),
        picturable_ids(move(picturable_ids)),
        click_position(move(click_position)),
        release_position(move(release_position)) {}

ClientEvent::ClientEvent(const ClientEvent &other) : ClientEvent(
        other.player_id,
        other.type,
        other.picturable_ids,
        other.click_position,
        other.release_position) {}

ClientEvent::ClientEvent(ClientEvent &&other) noexcept : ClientEvent(
        other.player_id,
        other.type,
        other.picturable_ids,
        move(other.click_position),
        move(other.release_position)) {
    other.player_id = 0;
}

ClientEvent &ClientEvent::operator=(const ClientEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = other.type;
    this->player_id = other.player_id;
    this->picturable_ids = other.picturable_ids;
    this->click_position = other.click_position;
    this->release_position = other.release_position;

    return *this;
}

ClientEvent &ClientEvent::operator=(ClientEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->type = other.type;
    this->player_id = other.player_id;
    this->picturable_ids = other.picturable_ids;
    this->click_position = move(other.click_position);
    this->release_position = move(other.release_position);

    other.player_id = 0;

    return *this;
}
