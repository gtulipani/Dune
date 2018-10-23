#include "PathFinder.h"

#include <vector>
#include <queue>
#include <stdexcept>

#include <iostream>

std::stack<Point> findPath(Terrain& t, Point start, Point goal, Unit u) {
    typedef std::pair<int, std::string> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
        std::greater<PQElement> > frontier;
    frontier.emplace(0, start.getStr());

    std::map<std::string, Point> came_from;
    std::map<std::string, int> cost_so_far;
    came_from[start.getStr()] = start;
    cost_so_far[start.getStr()] = 0;
  
    while (!frontier.empty()) {
        Point current = Point(frontier.top().second);
        frontier.pop();

        if (current == goal) {
            break;
        }

        for (Point next : t.getAdyacents(current, u)) {
            int new_cost = cost_so_far[current.getStr()] + t.getCost(current, next, u);
            if (cost_so_far.find(next.getStr()) == cost_so_far.end()
                || new_cost < cost_so_far[next.getStr()]) {
                cost_so_far[next.getStr()] = new_cost;
                int priority = new_cost + next.hDistanceTo(goal);
                frontier.emplace(priority, next.getStr());
                came_from[next.getStr()] = current;
            }
        }
    }

    Point current = goal;
    std::stack<Point> path;
    while (current != start) { 
        path.push(current);
        current = came_from[current.getStr()];
    }
    return path;
}

void testPathFinder() {
    Matrix m("Matrix");
    Terrain t(m);
    Unit u;
    std::stack<Point> path = findPath(t, Point(6, 3), Point(4, 14), u);
    while (!path.empty()) {
        std::cout << path.top().getStr() << ", ";
        path.pop();
    }
    std::cout << std::endl;
}
