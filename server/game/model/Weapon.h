#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <json/json.hpp>
#include <string>

struct Weapon {
	const std::string name;
	const unsigned int damage;
	const unsigned int shot_frequency;

	Weapon(const std::string& name, unsigned int damage, unsigned int shot_frequency);
};


#endif //__WEAPON_H__
