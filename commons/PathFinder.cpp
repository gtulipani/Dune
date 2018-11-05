#include <stack>
#include <unordered_map>

#include "PathFinder.h"
#include "Point.h"
#include "Unit.h"
#include "PriorityQueue.h"

std::stack<Point> findPath(Terrain &terrain, Point &start, Point &goal, Unit &u) {
    goal = terrain.findClosest(goal);

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

        std::vector<Point> adyacents = terrain.getAdyacents(current);
        u.filterBadTiles(adyacents);

        for (Point next : adyacents) {
            int new_cost = cost_so_far[current] +
                           terrain.getCost(current, next);

            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far.at(next)) {
                cost_so_far[next] = new_cost;
                int priority = new_cost + next.hDistanceTo(goal);
                frontier.push(next, priority);
                came_from[next] = current;
            }
        }
    }

    Point current = goal;
    std::stack<Point> path;
    while (current != start) {
        path.push(current);
        current = came_from[current];
    }
    return path;
}
