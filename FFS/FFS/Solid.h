#ifndef SOLID_H
#define SOLID_H

#include "Map_Object.h"

class Solid : public Map_Object{
public:
	Solid();
	void collision(Player *p);
	void collision(Projectile *p);
	void action(Player *p);

};


#endif // !SOLID_H