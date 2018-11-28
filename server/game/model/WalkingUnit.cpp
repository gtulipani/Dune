#include "WalkingUnit.h"

#include "PriorityQueue.h"
#include <Tick.h>
#include <TileUtils.h>
#include "Map.h"

WalkingUnit::WalkingUnit(Player& player, int id, int type, int health, const Point& size, const Point& initialPixelPosition, Map& map, int movespeed) :
SelectableGameObject(player, id, type, health, size, initialPixelPosition),
ticksPerStep(TO_TICKS(movespeed)),
tilePosition(tile_utils::getTileFromPixel(initialPixelPosition)),
map(map),
pixelGoal(initialPixelPosition) {}

void WalkingUnit::tick() {
    checkMovespeed();
}

void WalkingUnit::checkMovespeed() {
    if (GameObject::checkCounter(counter, ticksPerStep)) {
        Point prev_pos = this->pixelPosition;
        step();
        if (prev_pos != this->pixelPosition) {
            if (this->pixelPosition.row > prev_pos.row && this->pixelPosition.col > prev_pos.col) {
                sprite_direction = SPRITE_DOWN_RIGHT;
            }
            if (this->pixelPosition.row > prev_pos.row && this->pixelPosition.col == prev_pos.col) {
                sprite_direction = SPRITE_DOWN;
            }
            if (this->pixelPosition.row > prev_pos.row && this->pixelPosition.col < prev_pos.col) {
                sprite_direction = SPRITE_DOWN_LEFT;
            }
            if (this->pixelPosition.row == prev_pos.row && this->pixelPosition.col < prev_pos.col) {
                sprite_direction = SPRITE_LEFT;
            }
            if (this->pixelPosition.row < prev_pos.row && this->pixelPosition.col < prev_pos.col) {
                sprite_direction = SPRITE_UP_LEFT;
            }
            if (this->pixelPosition.row < prev_pos.row && this->pixelPosition.col == prev_pos.col) {
                sprite_direction = SPRITE_UP;
            }
            if (this->pixelPosition.row < prev_pos.row && this->pixelPosition.col > prev_pos.col) {
                sprite_direction = SPRITE_UP_RIGHT;
            }
            if (this->pixelPosition.row == prev_pos.row && this->pixelPosition.col > prev_pos.col) {
                sprite_direction = SPRITE_RIGHT;
            }
            haveIChanged = true;
            nextMotion();
        }
    }
}

void WalkingUnit::step() {
    if (path.empty()) {
        /*  Si path.empty() quiere decir que esta en el mismo tile que el goal.
            Entonces va directamente (si es que no llego ya). */
        if (pixelGoal != pixelPosition) {
            stepTo(pixelGoal);
        }
    } else {
        /*  Si no, entonces debe fijarse cual es el proximo tile. */
        Point &nextTile = path.top();
        if (nextTile == tile_utils::getTileFromPixel(pixelGoal)) {
            /*  Si el proximo tile es la meta final (o sea path tiene un solo
                elemento), va directamente. Esto es para no ir al centro de un
                tile y volver si el pixel estaba mas atras. */
            stepTo(pixelGoal);
            if (tilePosition != tile_utils::getTileFromPixel(pixelPosition)) {
                /*  Si cambie de tile, estoy en el goal. Debo actualizar mi tile
                    position y hacer pop(). path queda vacio, lugo va
                    directamente. */
                tilePosition = tile_utils::getTileFromPixel(pixelPosition);
                path.pop();
            }
        } else {
            /* Si el proximo no es la meta final, debo ir al centro del tile. */
            Point goalPixel = tile_utils::getTileCenter(nextTile);
            stepTo(goalPixel);
            if (tilePosition != tile_utils::getTileFromPixel(pixelPosition)) {
                /*  Solo hago el cambio de tile cuando llegue al centro, para
                    asegurarme de llegar a el. */
                if (pixelPosition == goalPixel) {
                    path.pop();
                    tilePosition = tile_utils::getTileFromPixel(pixelPosition);
                }
            }
        }
    }
}

void WalkingUnit::stepTo(const Point &pixel) {
    int row_dir = pixel.row - pixelPosition.row;
    int col_dir = pixel.col - pixelPosition.col;

    if (row_dir != 0) {
        row_dir = row_dir / std::abs(row_dir);
    }
    if (col_dir != 0) {
        col_dir = col_dir / std::abs(col_dir);
    }

    pixelPosition.row += row_dir;
    pixelPosition.col += col_dir;
}

void WalkingUnit::handleRightClick(const Point& pos) {
    pixelGoal = pos;
    Point goalTile = tile_utils::getTileFromPixel(pixelGoal);
    findPath(goalTile);
}

void WalkingUnit::findPath(const Point &goal) {
    PriorityQueue<Point> frontier;
    std::unordered_map<Point, Point> came_from;
    std::unordered_map<Point, int> cost_so_far;

    Point start = tilePosition;

    frontier.push(start, 0);
    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Point current = frontier.top();
        frontier.pop();

        if (current == goal) {
            break;
        }

        std::vector<Point> adyacents = map.getAdyacents(current);
        filterBadTiles(adyacents);

        for (Point next : adyacents) {
            int new_cost = cost_so_far[current] +
                           map.getCost(current, next);

            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far.at(next)) {
                cost_so_far[next] = new_cost;
                int priority = new_cost + next.hDistanceTo(goal);
                frontier.push(next, priority);
                came_from[next] = current;
            }
        }
    }

    path = std::stack<Point>(); // clears path

    if (came_from.find(goal) == came_from.end()) {
        return;
    }

    Point current = goal;
    while (current != start) {
        path.push(current);
        current = came_from[current];
    }
}
