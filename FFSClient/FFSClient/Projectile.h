#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Movement.hpp"
class Projectile : public Movement{
public:
	Projectile(int id,float x,float y,float alpha);
	void update();
	int get_id();
	std::pair <int,int> map_xy;
private:
	int id;
	
};


#endif