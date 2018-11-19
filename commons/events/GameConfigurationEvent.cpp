#include "GameConfigurationEvent.h"

GameConfigurationEvent::GameConfigurationEvent(int player_id, Matrix matrix) :
        player_id(player_id),
        matrix(std::move(matrix)) {}

GameConfigurationEvent::GameConfigurationEvent(const GameConfigurationEvent &other) : GameConfigurationEvent(
        other.player_id,
        other.matrix) {}

GameConfigurationEvent::GameConfigurationEvent(GameConfigurationEvent &&other) noexcept : GameConfigurationEvent(
        other.player_id,
        std::move(other.matrix)) {}

GameConfigurationEvent &GameConfigurationEvent::operator=(const GameConfigurationEvent &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->player_id = other.player_id;
    this->matrix = other.matrix;

    return *this;
}

GameConfigurationEvent &GameConfigurationEvent::operator=(GameConfigurationEvent &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->player_id = other.player_id;
    this->matrix = std::move(other.matrix);

    return *this;
}
