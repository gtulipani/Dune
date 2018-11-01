#include "Map.h"

Terrain Map::parseFile(const std::string &file) {
	Matrix m(file);
	return Terrain(m);
}

Map::Map(Terrain terrain) : terrain(std::move(terrain)) {}

Map::Map(const std::string &file) : Map(parseFile(file)) {}
