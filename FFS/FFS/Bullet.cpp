#include "Bullet.hpp"


#define PI 3.14159265


Bullet::Bullet(float alfa, float x, float y, int team ):
	Projectile(20,1000), speed(600)
{
	this->move_to(x,y);
	this->vx=cos(alfa*PI/180)*speed;
	this->vy=sin(alfa*PI/180)*speed;
	this->team=team;
}

Bullet::~Bullet(){
}

int Bullet::get_dmg(int multiplier){
	return (int)(dmg*multiplier);
}