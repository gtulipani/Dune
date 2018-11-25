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

static std::vector<Point> getPointsInLine(const Point& a, const Point& b) {
    std::vector<Point> pointsInLine;
    Point d = {b.row - a.row, b.col - b.row};
    Point d1 = {::abs(d.row), ::abs(d.col)};
    Point p = {2 * d1.col - d1.row, 2 * d1.row - d1.col};
    Point x, e;
    if (d1.col <= d1.row) {
        if (d.row >= 0) {
            x.row = a.row;
            x.col = a.col;
            e.row = b.row;
        } else {
            x.row = b.row;
            x.col = b.col;
            e.row = a.row;
        }
        pointsInLine.push_back(x);
        for (int i = 0; x.row < e.row; i++) {
            x.row = x.row + 1;
            if (p.row < 0) {
                p.row = p.row + 2 * d1.col;
            } else {
                if ((d.row < 0 && d.col < 0) || (d.row > 0 && d.col > 0)) {
                    x.col = x.col + 1;
                } else {
                    x.col = x.col - 1;
                }
                p.row = p.row + 2 * (d1.col - d1.row);
            }
            pointsInLine.push_back(x);
        }
    } else {
        if (d.col >= 0) {
            x.row = a.row;
            x.col = a.col;
            e.col = b.col;
        } else {
            x.row = b.row;
            x.col = b.col;
            e.col = a.col;
        }
        pointsInLine.push_back(x);
        for (int i = 0; x.col < e.col; i++) {
            x.col = x.col + 1;
            if (p.col <= 0) {
                p.col = p.col + 2 * d1.row;
            } else {
                if ((d.row < 0 && d.col < 0) || (d.row > 0 && d.col > 0)) {
                    x.row = x.row + 1;
                } else {
                    x.row = x.row - 1;
                }
                p.col = p.col + 2 * (d1.row - d1.col);
            }
            pointsInLine.push_back(x);
        }
    }
}

#include <iostream>

int main() {
    Point a = {2, 3};
    Point b = {8, 16};

    std::vector<Point> line = getPointsInLine(a, b);
    for (const Point& p : line) {
        std::cout << "(" << p.row << ", " << p.col << "), ";
    }
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

static std::vector<Point> fromTilesToPixels(const std::vector<Point>& tiles) {
    std::vector<Point> pixels;
    for (const Point& tile : tiles) {
        pixels.push_back(tile_utils::getTileCenter(tile));
    }
    return pixels;
}

static void removeReundantPoints(std::vector<Point>& pixelPath) {
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
