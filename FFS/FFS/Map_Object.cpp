#include "Map_Object.h"

Map_Object::Map_Object(int x,int y,Game *g,Map *m):
	game(g), x(x), y(y), map(m)
{

}

void Map_Object::collision(Player *p){

}

void Map_Object::collision(Projectile *p){

}

void Map_Object::action(Player *p){
	
}

void Map_Object::remove_player(Player *p){
	Players.erase(p);
}

void Map_Object::add_player(Player *p){
	if(Players.find(p)==Players.end())
		Players.emplace(p);
}

int Map_Object::get_id(){
	return id;
}

std::pair <int,int> Map_Object::get_xy(){
	return std::pair <int,int> (x,y);
}