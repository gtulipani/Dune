#include "Player.h"

Player::Player(int id) :
id(id) {}

void Player::addEspecia(int newEspecia) {
    especia += newEspecia;
}

bool Player::operator==(const Player& other) const {
    return this->id == other.id;
}
