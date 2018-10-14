#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include <string>
#include <stack>
#include <map>
#include "Matrix.h"
#include "Terrain.h"
#include "Unit.h"

std::stack<Point> findPath(Terrain& t, Point start, Point goal, Unit u);

void testPathFinder();

#endif
