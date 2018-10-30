#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include <json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

class Soldier {
private:
	string name;
	int level{};
	int speed{};
	float training_time{};
	int cost{};
	int life{};
public:
	Soldier() = default;

	// Functions that are used to be parsed by json
	friend void to_json(json &j, const Soldier &b);

	friend void from_json(const json &j, Soldier &b);
};

#endif //__SOLDIER_H__
