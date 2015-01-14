#include "Bullet.hpp"
#include "Gun.h"

Gun::Gun() : Weapon(20,20){
	name="Gun";
	cooldown_time=60;
}


Projectile * Gun::shoot(float alpha, float x, float y, int team){
	if(ready){
		ready=false;
		boost::thread t(boost::bind(&Weapon::cooldown,this));
		return new Bullet(alpha,x,y,team);

	}
	else{
		return NULL;
	}
}
