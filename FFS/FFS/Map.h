#ifndef MAP_H
#define MAP_H
#include "Map_Object_Factory.h"

class Map{
public:
	Map(std::string name, Game *g);
	void collision(Player *p);
	void collision(Projectile *p);
	void action(Player *p);
	void destroy_map_object(int x,int y,int z);
	void add_map_object(int x,int y,int z,Map_Object *mo);
	Map_Object* get_map_object(int x,int y,int z);
protected:
	std::vector<std::vector<std::vector<Map_Object*>>> Map_Matrix;
	int x,y;
};


#endif // !MAP_H
