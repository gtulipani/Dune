#include "PathFinder.h"

#include <vector>
#include "PriorityQueue.h"
#include <unordered_map>
#include <stdexcept>

#include <iostream>

/* hash function for storing Point on unordered_map */
namespace std {

  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& p) const
    {
      // Compute individual hash values for row and
      // col. Then combine them using XOR and bit
      // shifting
      return hash<std::size_t>()(p.row) ^ (hash<std::size_t>()(p.col) << 1);
    }
  };

}

std::stack<Point> findPath(Terrain& t, Point start, Point goal, Unit u) {
    PriorityQueue<Point> frontier;
    frontier.push(start, 0);
    std::unordered_map<Point, Point> came_from = {{start, start}};
    std::unordered_map<Point, int> cost_so_far = {{start, 0}};
  
    while (!frontier.empty()) {
        Point current = frontier.top();
        frontier.pop();

        if (current == goal) {
            break;
        }

        for (Point next : t.getAdyacents(current, u)) {
            int new_cost = cost_so_far[current] + t.getCost(current, next, u);

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

void testPathFinder() {
    Matrix m("Matrix");
    Terrain t(m);
    Unit u;
    std::stack<Point> path = findPath(t, Point(6, 3), Point(4, 14), u);
    while (!path.empty()) {
        std::cout << "(" << path.top().row << ", " << path.top().col << "), ";
        path.pop();
    }
    std::cout << std::endl;
}
