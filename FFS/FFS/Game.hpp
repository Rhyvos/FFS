#ifndef GAME_H	
#define GAME_H
#include <iostream>
#include "Player.hpp"
#include <set>

class Lobby;

class Game{
	public:
		Game(std::string name,int id,int team_size, int teams, Lobby* l);
		~Game();
		std::string get_name();

		void add_player(Player* p);
		void remove_player(Player* p);
		void start(int time);
		void game_end();
		void send(std::string msg);

		int players_number();
		int max_players();

		Game* get_game();

		void collisions(Player* p);
	private:
		Lobby* lobby;
		std::set<Player*> Players;
		void update();
		void build_map();
		void start_players();
		const int id;
		const std::string name;
		int team_size; 
		int teams;
};





#endif