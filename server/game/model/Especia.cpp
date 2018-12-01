#include "Especia.h"

#include <TileUtils.h>
#include <UnitsAndBuildings.h>

#include "GameObject.h"

#define ESPECIA_INITIAL_HEALTH 1000
#define ESPECIA_SPRITES 5

Especia::Especia(int id, const Point& tilePosition) :
Picturable(-1, id, ESPECIA, DEFAULT_SPRITE_DIRECTION, DEFAULT_SPRITE_MOTION, false, tile_utils::getTileTopLeft(tilePosition),
            {TILE_PIXEL_RATE, TILE_PIXEL_RATE}, ESPECIA_INITIAL_HEALTH, ESPECIA_INITIAL_HEALTH, 100) {
    especia_per_sprite_change = ESPECIA_INITIAL_HEALTH / ESPECIA_SPRITES;
}

Point Especia::getPosition() const {
    using namespace tile_utils;
    return getTileTopLeft(getTileFromPixel(position));
}

bool Especia::haveYouChanged() const {
    return haveIChanged;
}

bool Especia::runOut() const {
    return health <= 0;
}

#define TICKS_PER_ESPECIA 20

void Especia::tryToGetSome(int& especia) {
    if (GameObject::checkCounter(counter, TICKS_PER_ESPECIA)) {
        especia++;
        health--;
        for (int i = 0; i < ESPECIA_SPRITES; i++) {
            if (health <= ESPECIA_INITIAL_HEALTH - especia_per_sprite_change * i && health > ESPECIA_INITIAL_HEALTH - especia_per_sprite_change * (i + 1)) {
                if (sprite_motion != i) {
                    sprite_motion = i;
                    haveIChanged = true;
                    break;
                }
            }
        }
    }
}

void Especia::reset() {
    haveIChanged = false;
}
