#ifndef __MAP_H__
#define __MAP_H__

#include <string>
#include "Terrain.h"

using namespace std;

class Map {
private:
	Terrain terrain;

	Terrain parseFile(const string &file);
public:
	explicit Map(Terrain terrain);

	explicit Map(const string &file);
};


#endif //__MAP_H__
