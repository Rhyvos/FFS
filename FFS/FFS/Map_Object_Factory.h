#ifndef MAP_OBJECT_FACTORY_H
#define MAP_OBJECT_FACTORY_H
#include "Map_Object.h"
#include "Solid.h"
#include "Free.h"

class Map_Object_Factory{
public:
	Map_Object * Solid();
	Map_Object * Free();
};


#endif // !MAP_OBJECT_H