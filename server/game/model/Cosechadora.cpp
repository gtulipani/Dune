#include "Cosechadora.h"

#include "TileUtils.h"
#include "Map.h"

#include "Especia.h"

Cosechadora::Cosechadora(Player& player, int id, const Point& initialPosition, Map& map) :
WalkingUnit(player, id, COSECHADORA_UP, 1000, COSECHADORA_SIZE, initialPosition, map, COSECHADORA_MOVESPEED) {}

void Cosechadora::tick() {
    switch (state) {
        case going:
            this->WalkingUnit::tick();
            if (pixelPosition == pixelGoal) {
                state = collecting;
            }
            break;
        case collecting:
            if (!target->runOut()) {
                target->tryToGetSome(especia);
                if (especia >= ESPECIA_MAX) {
                    Point pos = map.findClosestRefineria(tile_utils::getTileFromPixel(pixelPosition));
                    this->WalkingUnit::handleRightClick(pos);
                    state = returning;
                }
            } else {
                Point pos = map.findClosestRefineria(tile_utils::getTileFromPixel(pixelPosition));
                this->WalkingUnit::handleRightClick(pos);
                state = returning;
            }
            break;
        case returning:
            this->WalkingUnit::tick();
            if (pixelPosition == pixelGoal) {
                player.addEspecia(ESPECIA_MAX);
                especia = 0;
                if (!target->runOut()) {
                    state = waiting;
                } else {
                    this->WalkingUnit::handleRightClick(target->getPosition());
                    state = going;
                }
            }
            break;
        case waiting:
            this->WalkingUnit::tick();
    }
}

void Cosechadora::handleRightClick(const Point& pos) {
    if (map.especiaAt(pos)) {
        target = map.getEspeciaAt(pos);
        this->WalkingUnit::handleRightClick(target->getPosition());
        state = going;
    } else {
        this->WalkingUnit::handleRightClick(pos);
    }
}
