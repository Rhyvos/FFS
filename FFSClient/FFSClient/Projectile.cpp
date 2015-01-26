#include "Projectile.h"


Projectile::Projectile(int id,float x,float y,float alpha) : 
Movement(60)
{
	#define PI 3.14159265
	this->move_to(x,y);
	this->vx=cos(alpha*PI/180)*600;
	this->vy=sin(alpha*PI/180)*600;
	this->id=id;
}

void Projectile::update(){
		vx+=ax/LOOP_PER_SECOND;
		vy+=ay/LOOP_PER_SECOND;
		x+=vx/LOOP_PER_SECOND;
		y+=vy/LOOP_PER_SECOND;
		al_draw_filled_circle(x,450-y, 2, al_map_rgb(0,0,0));
}

int Projectile::get_id(){
	return id;
}
