#ifndef GAME_H	
#define GAME_H
#include <iostream>
#include "Player.hpp"
#include <set>
class Game{
	public:
		Game(std::string name,int id,int team_size, int teams);
		~Game();
		std::string get_name();

		void add_player(Player* p);
		void remove_player(Player* p);
		void start();
		void send_msg(std::string msg);

		int players_number();
		int max_players();

		Game* get_game();
	private:
		std::set<Player*> Players;
		void update();
		const int id;
		const std::string name;
		int team_size; 
		int teams;
};





#endif