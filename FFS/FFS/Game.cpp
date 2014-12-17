#include "Game.hpp"
#include <iostream>
using namespace std;

		Game::Game(std::string name,int id,int team_size, int teams):
		id(id), name(name)
		{
			this->team_size=team_size;
			this->teams=teams;
		}

		std::string Game::get_name(){
			return name;
		}

		void Game::add_player(Player* p){
			if(Players.size()<team_size*teams){
				Players.insert(p);
				send_msg(p->get_name()+".join_game."+std::to_string(id)+"."+name+"\n");
			}
			else{
				p->send("error.Game is full\n");
			}
		}

		void Game::remove_player(Player* p){
			Players.erase(p);
			send_msg(p->get_name()+".leave_game."+std::to_string(id)+"."+name+"\n");
		}

		void Game::start(){

		}

		void Game::send_msg(std::string msg){
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
				(*it)->send(msg);
			}
		}

		int Game::players_number(){
			return Players.size();
		}
		
		int Game::max_players(){
			return team_size*teams;
		}

		Game* Game::get_game(){
			return this;
		}