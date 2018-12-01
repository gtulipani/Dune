#include "Cosechadora.h"

#include "TileUtils.h"
#include "Map.h"

#include "Especia.h"
#include "SiloOrRefinery.h"

Cosechadora::Cosechadora(Player& player, int id, const std::string& name, int health, const Point& size, const Point& initialPixelPosition,
                Map& map, int movespeed) :
WalkingUnit(player, id, name, health, size, initialPixelPosition, map, movespeed) {}

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
                if (player.silosAndRefineries.empty()) {
                    state = waiting;
                } else {
                    Point closestPos = player.silosAndRefineries.begin()->second->getPixelPosition();
                    for (auto& siloOrRefinery : player.silosAndRefineries) {
                        if (siloOrRefinery.second->getPixelPosition().hDistanceTo(pixelPosition) < closestPos.hDistanceTo(pixelPosition)) {
                            closestPos = siloOrRefinery.second->getPixelPosition();
                            store = siloOrRefinery.second;
                        }
                    }
                    this->WalkingUnit::handleRightClick(map.getClosestAvailablePoint(pixelPosition, closestPos));
                    state = returning;
                }
            }
            break;
        case returning:
            this->WalkingUnit::tick();
            if (pixelPosition == pixelGoal) {
                bool success = store->tryToStoreSome(especia);
                if (target->runOut() || !success) {
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

void Cosechadora::filterBadTiles(std::vector<Point> &tiles) const {
    for (auto it = tiles.begin(); it != tiles.end();) {
        if (map.mat.at(*it) == CIMAS || map.mat.at(*it) == PRECIPICIOS || map.mat.at(*it) == EDIFICIOS) {
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
}

void Cosechadora::nextMotion() {}
