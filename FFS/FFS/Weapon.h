#ifndef WEAPON_H
#define WEAPON_H
#include "Projectile.hpp"
class Weapon{
public:
	Weapon(int ammo, int max_ammo);
	
	virtual Projectile * shoot(float alpha, float x, float y,int team);
	void add_ammo(int ammo);
	int ammo_state();
	int get_max_ammo();
	std::string get_name();
	void cooldown();
	bool is_ready();

protected:
	int cooldown_time;
	bool ready;
	int current_ammo;
	int max_ammo;
	std::string name;
};



#endif