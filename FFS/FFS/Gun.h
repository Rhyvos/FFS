#ifndef GUN_H
#define GUN_H
#include "Weapon.h"

class Gun: public Weapon{
public:
	Gun();
	Projectile * shoot(float alpha, float x, float y, int team);

};

#endif