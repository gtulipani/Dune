#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <json/json.hpp>
#include <string>

#include "GameObject.h"

using namespace std;
using json = nlohmann::json;

class Player;

#define BUILDING_HEALTH 1000

class Building : public GameObject {
private:
	unsigned int counter = 0;
/*
	string name;
	int energy{};
	int cost{};
	string size;
	int structure_points{};
	int capacity{};
	*/
public:
	public:
    Building(Player& player, int _id, const Point& _size);

    virtual void tick() override;

    virtual void handleRightClick(Player& player, const Point& pos) override;

	void finishConstruction();

	void locateAt(const Point& _pixelPosition);

	// Functions that are used to be parsed by json
	//friend void to_json(json &j, const Building &b);

	//friend void from_json(const json &j, Building &b);
};


#endif //__BUILDING_H__
