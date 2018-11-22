#include "Player.h"

Player::Player(unsigned int id) :
id(id) {}

void Player::addEspecia(unsigned int newEspecia) {
    especia += newEspecia;
}
