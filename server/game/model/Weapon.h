#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

class Weapon {
private:
	string name;
	int damage{};
	int shoot_frequency{};
	int bonus{};
public:
	Weapon() = default;

	// Functions that are used to be parsed by json
	friend void to_json(json &j, const Weapon &b);

	friend void from_json(const json &j, Weapon &b);
};


#endif //__WEAPON_H__
