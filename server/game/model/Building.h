#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <json/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

class Building {
private:
	string name;
	int energy{};
	int cost{};
	string size;
	int structure_points{};
	int capacity{};
public:
	Building() = default;

	// Functions that are used to be parsed by json
	friend void to_json(json &j, const Building &b);

	friend void from_json(const json &j, Building &b);
};


#endif //__BUILDING_H__
