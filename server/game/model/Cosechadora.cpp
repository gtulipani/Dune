#include "Cosechadora.h"

#include "TileUtils.h"
#include "Map.h"

Cosechadora::Cosechadora(int id, const Point& initialPosition, Map& map) :
WalkingUnit(id, COSECHADORA_SIZE, initialPosition, map, COSECHADORA_MOVESPEED) {}

void Cosechadora::tick() {
    switch (state) {
        case going:
            WalkingUnit::tick();
            if (pixelPosition == pixelGoal) {
                state = collecting;
            }
            break;
        case collecting:
            if (GameObject::checkCounter(counter, TICKS_PER_UNIT_COLLECTED)) {
                especia++;
                if (especia >= ESPECIA_MAX) {
                    Point pos = map.findClosestRefineria(tile_utils::getTileFromPixel(pixelPosition));
                    WalkingUnit::handleRightClick(pos);
                    state = returning;
                }
            }
            break;
        case returning:
            WalkingUnit::tick();
            if (pixelPosition == pixelGoal) {
                //player.addEspecia(200);
                especia = 0;
                WalkingUnit::handleRightClick(target);
                state = going;
            }
            break;
        case waiting:
            WalkingUnit::tick();
    }
}

void Cosechadora::handleRightClick(const Point& pos) {
    if (map.especiaAt(pos)) {
        target = tile_utils::getTileCenter(pos);
        WalkingUnit::handleRightClick(target);
        state = going;
    } else {
        WalkingUnit::handleRightClick(pos);
    }
}
