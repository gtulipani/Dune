#include "GameControler.h"

#include <TileUtils.h>

#include "../model/Map.h"
#include "../model/GameObject.h"
#include "../model/WalkingUnit.h"
#include "../model/Cosechadora.h"
#include "../model/Especia.h"
#include "../model/Building.h"

GameControler::GameControler(Map& _map) :  map(_map) {}

void GameControler::initialize(unsigned int number_of_players) {

    for (unsigned int i = 0; i < number_of_players; i++) {
        players.emplace_back();
        selectedObjects.push_back(nullptr);
    }

    unsigned int i = 0;
    for (Point tilePosition : map.constructionCenterPositions) {
        Point pixelPosition = tile_utils::getTileTopLeft(tilePosition);
        GameObject* constructionCenter = new Building(players.at(i++), next_id++, Point(TILE_PIXEL_RATE * 3, TILE_PIXEL_RATE * 3), pixelPosition);
        gameObjects.push_back(constructionCenter);
        map.update(EDIFICIOS, Point(3, 3), tilePosition);
    }

    std::vector<Especia*> especias = map.generateEspeciaFromId(next_id);
    for (Especia* especia : especias) {
        gameObjects.push_back(especia);
        next_id++;
    }
}

void GameControler::tick() {
    for (GameObject* gameObject : gameObjects) {
        // We let know all the objects that time has passed
        gameObject->tick();
    }
}

void GameControler::leftClick(unsigned int player_id, const Point& point) {
    if (selectedObjects.at(player_id) != nullptr) {
        selectedObjects.at(player_id)->unselect();
        selectedObjects.at(player_id) = nullptr;
    }
    for (GameObject* gameObject : gameObjects) {
        bool success = gameObject->tryToSelect(point);
        if (success) {
            selectedObjects.at(player_id) = gameObject;
            break;
        }
    }
}

void GameControler::rightClick(unsigned int player_id, const Point& point) {
    if (selectedObjects.at(player_id) != nullptr) {
        selectedObjects.at(player_id)->handleRightClick(players.at(player_id), point);
    }
}

void GameControler::createWalkingUnit(unsigned int player_id, const Point& point) {
    auto * unit = new WalkingUnit(players.at(player_id), next_id++, {32, 32}, point, map, 10);
    gameObjects.push_back(unit);
}

void GameControler::createCosechadora(unsigned int player_id, const Point& point) {
    auto * unit = new Cosechadora(players.at(player_id), next_id++, point, map);
    gameObjects.push_back(unit);
}

std::vector<Picturable> GameControler::getStates() {
    std::vector<Picturable> states;
    for (GameObject* gameObject : gameObjects) {
        if (gameObject->haveYouChanged()) {
            states.push_back(gameObject->getState());
        }
    }
    return states;
}

void GameControler::updateGameObjects() {
    unsigned int n = gameObjects.size();
    for (unsigned int i = 0; i < n; i++) {
        if (gameObjects.at(i)->isDead()) {
            delete gameObjects.at(i);
            gameObjects.erase(gameObjects.begin() + i);
        }
    }
}
