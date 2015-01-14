

#include "Game.hpp"
#include "Lobby.hpp"
#include "Player.hpp"

using namespace std;

		

		Game::Game(std::string name,int id,int team_size, int teams, Lobby* l):
		id(id), name(name), lobby(l), timer(NULL), event_queue(NULL)
		{
			this->team_size=team_size;
			this->teams=teams;
			this->time=7200;
			running =false;
			projectile_id=0;
		}
		Game::~Game(){
			Players.clear();
			for(list<Projectile*>::iterator it=Projectiles.begin(); it!=Projectiles.end(); it++){
				delete (*it);
			}
			time=0;
			boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			al_destroy_timer(timer);
			al_destroy_event_queue(event_queue);
			
		}

		std::string Game::get_name(){
			return name;
		}

		void Game::add_player(Player* p){
			if(Players.size()<team_size*teams){
				p->send("game,create");

				for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++)
					p->send("game,join_game,"+(*it)->get_name()+","+(*it)->get_id()+","+name);

				
				Players.insert(p);
				boost::this_thread::sleep(boost::posix_time::milliseconds(100));
				this->send("game,join_game,"+p->get_name()+","+p->get_id()+","+name);

				
				if(Players.size()==1&&!running)
					boost::thread t(boost::bind(&Game::start,this));
			}
			else{
				p->send("error,Game is full");
				return;
			}

			if(running){
				p->in_game=true;
				p->set_team(rand()%teams);
				p->reset();
				p->move_to(rand()%640,0);
				send("player,"+p->get_id()+",team,"+to_string(p->get_team()));
				for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++)
					p->send("player,"+(*it)->get_id()+",move_to,"+(*it)->get_string_x()+","+(*it)->get_string_y());
				this->send("player,"+p->get_id()+",move_to,"+p->get_string_x()+","+p->get_string_y());
				p->send("game,start");
			}


			
		}

		void Game::remove_player(Player* p){
			this->send("game,leave_game,"+p->get_id()+","+std::to_string(id)+","+name);
			Players.erase(p);
			p->in_game=false;
			
		}

		void Game::start(){
			try{

			
 
			timer = al_create_timer(1.0 / 60.0);
			if(!timer) {
				  fprintf(stderr, "failed to create timer!\n");
				  return;
			}



			event_queue = al_create_event_queue();
				if(!event_queue) {
				fprintf(stderr, "failed to create event_queue!\n");
				al_destroy_timer(timer);
				return ;
			}

			for(int i=0;i<10;i++){
				
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
			}
			
			if(Players.size()==0){
				send("game,stop");
				game_end();
				lobby->remove_game(this);
				return;
			}
			running=true;
			build_map();
			start_players();
			send("game,start");
			al_register_event_source(event_queue,al_get_timer_event_source(timer));
			al_start_timer(timer);
			ALLEGRO_EVENT ev;
					

				while(time){
					al_wait_for_event(event_queue, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER) {
						update();
					}else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{ 
						cout<<"ALLEGRO_EVENT_DISPLAY_CLOSE"<<endl;
						return; 
					}
				
				
					time--;
				}
			
			

			send("game,end");
			game_end();
			lobby->remove_game(this);
			}
			catch(exception ex){
				cout<<ex.what()<<endl;
			}
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
					(*it)->move_to(rand()%640,0);
					send("player,"+(*it)->get_id()+",team,"+to_string(j));
					this->send("player,"+(*it)->get_id()+",move_to,"+(*it)->get_string_x()+","+(*it)->get_string_y());
					
				}
				
			}
			
		}

		void Game::build_map(){
		}

		void Game::update(){
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
				collisions(*it);
				(*it)->update();
			}
			for(list<Projectile*>::iterator it=Projectiles.begin(); it!=Projectiles.end() ; it++){
				if((*it)->is_alive()){
					(*it)->update();
				}

				
			}
		}
float iloczyn(float x1, float y1, float x2,float y2, float x3, float y3) { 
			return (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);    //zwracamy iloczyn skalarny wektorów (p2-p1) i (p3-p1)
		}
		void Game::collisions(Player* p){
			float x=p->get_next_x();
			float y=p->get_next_y();
			if(x<0||x>640){
				p->instant_stop_x();
				if(x<0)
					p->move_to(0,p->get_y());
				if(x>640)
					p->move_to(640,p->get_y());
				send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
			}
			if(y<0||y>480){
				p->instant_stop_y();
				if(y<0)
					p->move_to(p->get_x(),0);
				if(y>480)
					p->move_to(p->get_x(),480);
				send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
			}

			for(list<Projectile*>::iterator it=Projectiles.begin(); it!=Projectiles.end(); it++){
				float S_1 = iloczyn((*it)->get_x(),(*it)->get_y(), p->get_x(), p->get_y() , (*it)->get_next_x(),(*it)->get_next_y());
				float S_2 = iloczyn((*it)->get_x(),(*it)->get_y(), p->get_x(), p->get_y()+75, (*it)->get_next_x(),(*it)->get_next_y());
				float S_3 = iloczyn(p->get_x(), p->get_y() , (*it)->get_x(),(*it)->get_y(), p->get_x(), p->get_y()+75);
				float S_4 = iloczyn(p->get_x(), p->get_y() , (*it)->get_x(),p->get_y()+75, p->get_x(), p->get_y()+75);
				if (((S_1 > 0 && S_2 < 0) || (S_1 < 0 && S_2 > 0)) && ((S_3 < 0 && S_4 > 0) || (S_3 > 0 && S_4 < 0))){
					send("player,"+p->get_id()+",hp,"+to_string((*it)->get_dmg(1)));
				}
			}




		}

		

		void Game::game_end(){
			for(set<Player*>::iterator it=Players.begin(); it!=Players.end()  ; it++){
				(*it)->end_game();
			}
			running =false;
		}

		void Game::add_projectile(Projectile *p){
			p->set_id(projectile_id++);
			Projectiles.push_back(p);
			cout<<p->get_string_x()+","+p->get_string_y()<<endl;
			send("game,add_projectile,"+to_string(p->get_id())+","+p->get_string_x()+","+p->get_string_y()+","+to_string(p->get_alpha())+","+to_string(p->get_team()));
		}
