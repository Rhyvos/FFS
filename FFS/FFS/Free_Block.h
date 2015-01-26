#ifndef FREE_BLOCK_H
#define FREE_BLOCK_H

#include "Map_Object.h"

class Free_Block: public Map_Object{
public:
	Free_Block(int x,int y,Game *g,Map *m);
	void collision(Player *p);
	void collision(Projectile *p);
	void action(Player *p);

};


#endif // !FREE_H