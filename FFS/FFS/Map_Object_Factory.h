#ifndef MAP_OBJECT_FACTORY_H
#define MAP_OBJECT_FACTORY_H
#include "Map_Object.h"
#include "Solid_Block.h"
#include "Free_Block.h"

class Map_Object_Factory{
public:
	Map_Object_Factory(Game *g, Map *m);
	Map_Object * Solid(int x, int y);
	Map_Object * Free(int x, int y);
private:
	Game *g;
	Map *map;
};


#endif // !MAP_OBJECT_H