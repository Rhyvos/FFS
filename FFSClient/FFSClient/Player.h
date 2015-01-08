#ifndef PLAYER_H
#define PLAYER_H
#include "Movement.hpp"


class Player : public Movement{
public:
	Player(std::string name, int id);
	void shoot();
	ALLEGRO_BITMAP get_model();
	std::string get_name();
	int get_id();
	void read_msg(std::vector<std::string> msg);
private:
	std::string name;
	int id;
	int team;
	int actual_weapon;
	int hp;
	ALLEGRO_BITMAP *model;
	ALLEGRO_BITMAP *weapon;
};


#endif