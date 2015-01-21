#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "Player.hpp"
#include "Projectile.hpp"



class Map;

class Map_Object{
public:
	Map_Object(int x,int y,Game *g, Map*m);
	virtual void collision(Player *p);
	virtual void collision(Projectile *p);
	virtual void action(Player *p);
	void remove_player(Player *p);
	void add_player(Player *p);
	int get_id();
	std::pair <int,int> get_xy();
protected:
	std::set<Player *> Players;
	Game *game;
	Map *map;
	int x,y;
	int id;
};


#endif // !MAP_OBJECT_H
