#include "PathingAlgorithms.h"

#include <TileUtils.h>
#include <PriorityQueue.h>

#include "Map.h"
#include "WalkingUnit.h"

std::stack<Point> pathing::findPath(const Map& map,
                                    const WalkingUnit& unit,
                                    const Point& start,
                                    const Point& goal)
{
    Point tile_start = tile_utils::getTileFromPixel(start);
    Point tile_goal = tile_utils::getTileFromPixel(goal);
    std::vector<Point> tile_path = a_star(map, unit, tile_start, tile_goal);
    std::vector<Point> pixelPath = fromTilesToPixels(tile_path);
    pixelPath.push_back(goal);
    removeReundantPoints(pixelPath);
    return {};
}

/* Finds tile pathing */
static std::vector<Point> a_star(const Map& map,
                                const WalkingUnit& unit,
                                const Point& start,
                                const Point& goal)
{
    PriorityQueue<Point> frontier;
    std::unordered_map<Point, Point> came_from;
    std::unordered_map<Point, int> cost_so_far;

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
        unit.filterBadTiles(adyacents);

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

    std::vector<Point> tiles;

    if (came_from.find(goal) == came_from.end()) {
        return tiles;
    }

    Point current = goal;
    while (current != start) {
        tiles.push_back(current);
        current = came_from[current];
    }
    tiles.push_back(start);

    return tiles;
}

std::vector<Point> fromTilesToPixels(const std::vector<Point>& tiles) {
    std::vector<Point> pixels;
    for (const Point& tile : tiles) {
        pixels.push_back(tile_utils::getTileCenter(tile));
    }
    return pixels;
}

void removeReundantPoints(std::vector<Point>& pixelPath) {
    std::vector<Point> newPixelPath;

    Point current_point = pixelPath.at(0);
    Point next_point = pixelPath.at(1);

    Point prev_direction = Point(next_point.row - current_point.row, next_point.col - current_point.col).getDirection();
    Point next_direction;

    current_point = next_point;

    int n = pixelPath.size();
    for (int i = 2; i < n; i++) {
        next_point = pixelPath.at(i);
        next_direction = Point(next_point.row - current_point.row, next_point.col - current_point.col).getDirection();
        if (prev_direction != next_direction) {
            newPixelPath.push_back(current_point);
        }
        current_point = next_point;
        prev_direction = next_direction;
    }

    newPixelPath.push_back(current_point);
}
