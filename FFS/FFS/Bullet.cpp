#include "Bullet.hpp"


#define PI 3.14159265


Bullet::Bullet(float x, float y, float alfa, int team):
	Projectile(20,1000), speed(150)
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