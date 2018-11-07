#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include <json/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

class Vehicle {
private:
	string name;
	int level{};
	int speed{};
	int build_time{};
	int cost{};
	int life{};
public:
	Vehicle() = default;

	// Functions that are used to be parsed by json
	friend void to_json(json &j, const Vehicle &b);

	friend void from_json(const json &j, Vehicle &b);
};


#endif //__VEHICLE_H__
