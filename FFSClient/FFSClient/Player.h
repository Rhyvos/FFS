#ifndef PLAYER_H
#define PLAYER_H
#include "Movement.hpp"

class Game;
class Player : public Movement{
public:
	Player(std::string name, int id, Game *g);
	~Player();
	void shoot(float alpha);
	ALLEGRO_BITMAP get_model();
	std::string get_name();
	int get_id();
	void read_msg(std::vector<std::string> msg);
	void update();
private:
	Game * game;
	std::string name;
	int id;
	int team;
	int actual_weapon;
	int hp;
	ALLEGRO_BITMAP *model;
	ALLEGRO_BITMAP *weapon;
};


#endif