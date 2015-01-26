#include "Map_Object_Factory.h"



Map_Object_Factory::Map_Object_Factory(Game *g,Map *m): g(g), map(m){


}

Map_Object * Map_Object_Factory::Solid(int x, int y){
	return new Solid_Block(x,y,g,map);
}

Map_Object * Map_Object_Factory::Free(int x, int y){
	return new Free_Block(x,y,g,map);
}
