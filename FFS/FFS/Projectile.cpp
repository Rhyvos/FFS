#include "Projectile.hpp"

Projectile::Projectile(int dmg,int life):
	dmg(dmg), Movement(60)
{
	this->life=life;		//-1:infinite, 0<:life time 60=1s
}

int Projectile::get_dmg(float multiplier){
	return 0;
}

Projectile::~Projectile(){
}

int Projectile::get_team(){
	return team;
}
bool Projectile::is_alive(){
	if(life==0)
		return false;
	else
		return true;
}

void Projectile::update(){
		vx+=ax/LOOP_PER_SECOND;
		vy+=ay/LOOP_PER_SECOND;
		x+=vx/LOOP_PER_SECOND;
		y+=vy/LOOP_PER_SECOND;
		life--;
}
