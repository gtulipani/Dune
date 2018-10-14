#include "PathFinder.h"

#include <vector>
#include <queue>
#include <stdexcept>

#include <iostream>

compare::compare(std::map<std::string, int>& _priorityMap)
: priorityMap(_priorityMap) {}

void compare::set(Point p, int priority) {
    priorityMap[p.getStr()] = priority;
}

bool compare::operator() (const Point& a, const Point& b) const {
    return priorityMap.at(a.getStr()) > priorityMap.at(b.getStr());
}

PathFinder::PathFinder() : comp(priorityMap) {}

std::stack<Point>PathFinder:: getPath(Terrain& t, Point start, Point goal, Unit u) {
    /* A* Algorithm */
    std::priority_queue<Point ,std::vector<Point>, compare> frontier(comp);
    comp.set(start, 0);
    frontier.push(start);

    std::map<std::string, Point> came_from;
    std::map<std::string, int> cost_so_far;
    came_from[start.getStr()] = start;
    cost_so_far[start.getStr()] = 0;

    Point current = start;
    int new_cost;
    int priority;
    bool alreadyVisited;
    while (!frontier.empty()) {
        current = frontier.top();
        frontier.pop();

        if (current == goal) {
            break;
        }
    
        std::vector<Point> adyacents = t.getAdyacents(current, u);
        for (auto it = adyacents.begin(); it != adyacents.end(); ++it) {
            new_cost = cost_so_far[current.getStr()] + t.getCost(current, (*it), u);
            alreadyVisited = cost_so_far.find(it->getStr()) != cost_so_far.end();
            if (!alreadyVisited || new_cost < cost_so_far.at(it->getStr())) {
                cost_so_far[it->getStr()] = new_cost;
                priority = new_cost + goal.hDistanceTo(*it);
                comp.set(*it, priority);
                frontier.push(*it);
                came_from[it->getStr()] = current;
            }
        }
    }

    current = goal;
    std::stack<Point> path;
    while (current != start) { 
        path.push(current);
        current = came_from[current.getStr()];
    }
    return path;
    /*  El algroitmo funciona bien, hay que ajustar los costos de las diagonales
        para que no las elija siempre. */
}

void testPathFinder() {
    Matrix m("Matrix");
    Terrain t(m);
    PathFinder pf;
    Unit u;
    std::stack<Point> path = pf.getPath(t, Point(6, 3), Point(4, 14), u);
    while (!path.empty()) {
        std::cout << path.top().getStr() << ", ";
        path.pop();
    }
    std::cout << std::endl;
}
