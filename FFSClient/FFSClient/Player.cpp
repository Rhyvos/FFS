#include "Player.h"

using namespace std;

Player::Player(std::string name, int id) : Movement(60)
{
	this->name=name;
	this->id=id;
	cout<<"New Player: "<<name<<" id:"<<id<<endl;
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
		shoot();
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
	}


}

std::string Player::get_name(){
	return name;
}

int Player::get_id(){
	return id;
}



void Player::shoot(){
	cout<<"shoot"<<endl;
}