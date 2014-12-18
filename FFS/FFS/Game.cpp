#include "Game.hpp"
#include <iostream>
#include <boost/thread.hpp>
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
				send(p->get_name()+".join_game."+std::to_string(id)+"."+name+"\n");
				if(Players.size()==max_players())
					boost::thread t(boost::bind(&Game::start,this,1800));
			}
			else{
				p->send("error.Game is full\n");
			}
		}

		void Game::remove_player(Player* p){
			Players.erase(p);
			send(p->get_name()+".leave_game."+std::to_string(id)+"."+name+"\n");
		}

		void Game::start(int time){
			for(int i=0;i<10;i++){
				send("game.start."+to_string(10-i)+"\n");
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			}
			if(Players.size()!=max_players()){
				send("game.stop\n");
				return;
			}

			build_map();
			start_players();

			while(time){
				update();
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000/60));
				time--;
			}

			send("game.end\n");
			game_end();
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
					send("player."+(*it)->get_name()+".team."+to_string(j)+"\n");
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

				send("player."+p->get_name()+".instant_stop_x\n");
			}
			if(y<0||y>100){
				p->instant_stop_y();
				if(y<0)
					p->move_to(p->get_x(),0);
				if(y>100)
					p->move_to(p->get_x(),100);
				send("player."+p->get_name()+".instant_stop_y\n");
			}

		}

		void Game::game_end(){
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end()  ; it++){
				(*it)->end_game();
			}
		}