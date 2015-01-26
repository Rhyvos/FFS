#include "Weapon.h"


Weapon::Weapon(int ammo, int ammo_limit){
	this->current_ammo=ammo;
	this->max_ammo=ammo_limit;
	name="weapon class";
	cooldown_time=0;
	ready=true;
}


void Weapon::add_ammo(int ammo){
	if(ammo+current_ammo<=max_ammo)
		current_ammo+=ammo;
	else
		current_ammo=max_ammo;
}

int Weapon::ammo_state(){
	return current_ammo;
}

int Weapon::get_max_ammo(){
	return max_ammo;
}

std::string Weapon::get_name(){
	return name;
}

Projectile * Weapon::shoot(float alpha, float x, float y,int team){
	return NULL;
}

void Weapon::cooldown(){
	boost::this_thread::sleep(boost::posix_time::milliseconds(cooldown_time));
	ready=true;
}

bool Weapon::is_ready(){
	return ready;
}




