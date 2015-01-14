#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "Player.hpp"
#include "Projectile.hpp"
class Map_Object{
public:
	Map_Object();
	virtual void collision(Player *p);
	virtual void collision(Projectile *p);
	virtual void action(Player *p);
	void remove_player(Player *p);
	void add_player(Player *p);
protected:
	std::set<Player *> Players;
};


#endif // !MAP_OBJECT_H
