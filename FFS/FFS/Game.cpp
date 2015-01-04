#include "Game.hpp"
#include <iostream>
#include <boost/thread.hpp>
#include "Lobby.hpp"
#include "Player.hpp"
using namespace std;

		Game::Game(std::string name,int id,int team_size, int teams, Lobby* l):
		id(id), name(name), lobby(l)
		{
			this->team_size=team_size;
			this->teams=teams;
		}
		Game::~Game(){
			Players.clear();

		}

		std::string Game::get_name(){
			return name;
		}

		void Game::add_player(Player* p){
			if(Players.size()<team_size*teams){
				Players.insert(p);
				send("player,join_game,"+p->get_name()+","+std::to_string(id)+","+name);
				if(Players.size()==max_players())
					boost::thread t(boost::bind(&Game::start,this,1800));
			}
			else{
				p->send("error,Game is full");
			}
		}

		void Game::remove_player(Player* p){
			Players.erase(p);
			send("leave_game,"+p->get_name()+","+std::to_string(id)+","+name);
		}

		void Game::start(int time){
			for(int i=0;i<10;i++){
				send("game,start,"+to_string(10-i));
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			}
			if(Players.size()!=max_players()){
				send("game,stop");
				return;
			}

			build_map();
			start_players();

			while(time){
				update();
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000/60));
				time--;
			}

			send("game,end");
			game_end();
			lobby->remove_game(this);
		}

		void Game::send(std::string msg){
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


		void Game::start_players(){
			int i=0;
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end() && i<team_size ; i++){
				for(int j=0 ; it!=Players.end() && j<teams ; j++, it++){
					(*it)->in_game=true;
					(*it)->set_team(j);
					(*it)->reset();
					(*it)->move_to(rand()%100,rand()%100);
					this->send("player,"+(*it)->get_name()+",move_to,"+(*it)->get_string_x()+","+(*it)->get_string_y());
					send("player,"+(*it)->get_name()+",team,"+to_string(j));
				}
				
			}
			
		}

		void Game::build_map(){
		}

		void Game::update(){
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
				collisions(*it);
				(*it)->update();
				cout<<"["<<(*it)->get_name()<<"] x:"<<(*it)->get_x()<<" y:"<<(*it)->get_y()<<endl;
			}
		}

		void Game::collisions(Player* p){
			float x=p->get_next_x();
			float y=p->get_next_y();
			if(x<0||x>100){
				p->instant_stop_x();
				if(x<0)
					p->move_to(0,p->get_y());
				if(x>100)
					p->move_to(100,p->get_y());

				send("player,"+p->get_name()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
			}
			if(y<0||y>100){
				p->instant_stop_y();
				if(y<0)
					p->move_to(p->get_x(),0);
				if(y>100)
					p->move_to(p->get_x(),100);
				send("player,"+p->get_name()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
			}

		}

		void Game::game_end(){
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end()  ; it++){
				(*it)->end_game();
			}
		}