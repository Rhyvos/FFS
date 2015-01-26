#ifndef SOLID_BLOCK_H
#define SOLID_BLOCK_H

#include "Map_Object.h"

class Solid_Block : public Map_Object{
public:
	Solid_Block(int x,int y,Game *g,Map *m);
	void collision(Player *p);
	void collision(Projectile *p);
	void action(Player *p);

};


#endif // !SOLID_H