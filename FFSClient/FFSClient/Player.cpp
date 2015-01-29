#include "Player.h"
#include "Game.hpp"
#include "Projectile.h"
using namespace std;

Player::Player(std::string name, int id, Game *g) : Movement(60)
{
	this->game=g;
	this->name=name;
	this->id=id;
}

Player::~Player(){
	al_destroy_bitmap(model);
	al_destroy_bitmap(weapon);
}


void Player::read_msg(std::vector<std::string> msg){


	if(!msg[2].compare("start_move")){
		move_to(stof(msg[4]),stof(msg[5]));
		start_move(stof(msg[3]));
	}else if(!msg[2].compare("jump")){
		move_to(stof(msg[4]),stof(msg[5]));
		jump(stof(msg[3]));
	}else if(!msg[2].compare("stop_move")){
		move_to(stof(msg[4]),stof(msg[5]));
		stop_move();
	}else if(!msg[2].compare("shoot")){
		shoot(0.0);
	}else if(!msg[2].compare("swap_weapon")){
		cout<<name<<" swap weapon"<<endl;
	}else if(!msg[2].compare("action")){
		cout<<name<<" action"<<endl;
	}else if(!msg[2].compare("team")){
		team=stoi(msg[3]);
	}else if(!msg[2].compare("move_to")){
		move_to(stof(msg[3]),stof(msg[4]));
	}else if(!msg[2].compare("instant_stop_x")){
		move_to(stof(msg[3]),stof(msg[4]));
		instant_stop_x();

	}else if(!msg[2].compare("instant_stop_y")){
		move_to(stof(msg[3]),stof(msg[4]));
		instant_stop_y();

	}else if(!msg[2].compare("hp")){
		hp=stof(msg[3]);
	}else if(!msg[2].compare("fall")){
		move_to(stof(msg[3]),stof(msg[4]));
		fall();
	}


}

std::string Player::get_name(){
	return name;
}

int Player::get_id(){
	return id;
}

void Player::update(){
	Movement::update();
	if(hp!=0)
		al_draw_filled_rectangle(x-25,map_xy.second*50-y, x+25,map_xy.second*50-75-y, al_map_rgb(100-hp,hp,0));
	else
		al_draw_rectangle(x-25,map_xy.second*50-y, x+25,map_xy.second*50-75-y, al_map_rgb(0,0,0),2);
}



void Player::shoot(float alpha){
	
}