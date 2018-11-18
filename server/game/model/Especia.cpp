#include "Especia.h"

#include "TileUtils.h"

Especia::Especia(int id, const Point& initialPosition) :
GameObject(id, Point(TILE_PIXEL_RATE, TILE_PIXEL_RATE), initialPosition) {
    health = INITIAL_ESPECIA;
}

Point Especia::getPosition() const {
    using namespace tile_utils;
    return getTileCenter(getTileFromPixel(pixelPosition));
}

void Especia::tick() {}

void Especia::handleRightClick(const Point& p) {}

bool Especia::hasEspeciaLeft() const {
    return !isDead();
}

const unsigned int TICKS_PER_UNIT_COLLECTED = 20;

void Especia::tryToGetSome(unsigned int& cosechadoraEspecia) {
    if (GameObject::checkCounter(counter, TICKS_PER_UNIT_COLLECTED) && health != 0) {
        cosechadoraEspecia++;
        health--;
    }
}
