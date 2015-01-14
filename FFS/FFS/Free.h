#ifndef FREE_H
#define FREE_H

#include "Map_Object.h"

class Free: public Map_Object{
public:
	Free();
	void collision(Player *p);
	void collision(Projectile *p);
	void action(Player *p);

};


#endif // !FREE_H