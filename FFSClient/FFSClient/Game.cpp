#include "Game.hpp"
#include "Socket_session.h"
#include "Map.h"
#define PI 3.14159265
const float FPS = 60;

using namespace std;

Game::Game(Socket_session *session) : 
	session(session), display(NULL),event_queue(NULL),timer(NULL),map(NULL)
{
	stop=false;
	client_player=NULL;
}

Game::~Game(){
	stop=true;
	for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
		delete (*it);
	}
	/*for(set<Projectile*>::iterator it=Projectiles.begin(); it!=Projectiles.end() ; it++){
		delete (*it);
	}*/
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_timer(timer);
}



Player * Game::find_player(std::string name){
	for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
		if(!(*it)->get_name().compare(name)){
			return (*it);
		}

			
	}
	return NULL;

}

Player * Game::find_player(int id){
	for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
		if((*it)->get_id()==id){
			return (*it);
		}

			
	}
	return NULL;

}



void Game::add_player(Player *p){
	Players.insert(p);
	if(p->get_id()==player_id)
	client_player=p;

	
}

void Game::remove_player(Player *p){
	Players.erase(p);	
}



void Game::start(){
	
	redraw=true;
	
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return;
   }
   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return ;
   }
	al_init_font_addon(); 
	al_init_ttf_addon();
	font = al_load_ttf_font("Arial.ttf",10,0 );
   if (!font){
			  fprintf(stderr, "Could not load 'Arial.ttf'.\n");
			  return ;
		   }
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return ;
   }
   al_init_image_addon();
   al_init_primitives_addon();
   al_install_keyboard();
	al_install_mouse();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_timer_event_source(timer));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_start_timer(timer);
	ALLEGRO_EVENT ev;
	map=new Map("Map1.txt");
	al_set_target_bitmap(al_get_backbuffer(display));
	for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
		(*it)->map_xy=map->get_xy();
	}
	while(!stop)
   {


	  al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		  session->write("leave_game");
         stop=true;
      }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         if(ev.keyboard.keycode == ALLEGRO_KEY_W) {
			 session->write("jump,240.0");
			 //boost::thread t(boost::bind(&Socket_session::write,session,"jump,30.0"));
         }
		 if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
			 session->write("start_move,100.0");
			 //boost::thread t(boost::bind(&Socket_session::write,session,"start_move,20.0"));
         }
		 if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
			 session->write("start_move,-100.0");
			 //boost::thread t(boost::bind(&Socket_session::write,session,"start_move,-20.0"));
         }
      }else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
		 if(ev.keyboard.keycode == ALLEGRO_KEY_D) {

			 boost::thread t(boost::bind(&Socket_session::write,session,"stop_move,0.0"));
         }
		 if(ev.keyboard.keycode == ALLEGRO_KEY_A) {

			 boost::thread t(boost::bind(&Socket_session::write,session,"stop_move,0.0"));
         }
	  }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		  if(ev.mouse.button==1&&client_player!=NULL){
				int x=(float)ev.mouse.x-client_player->get_x();
				int y=(float)(350-ev.mouse.y)-client_player->get_y();
				float alpha=atan2 (y,x) * 180 / PI;
				session->write("shoot,"+to_string(alpha));
		  }

				
	  }

      if(redraw && al_is_event_queue_empty(event_queue)) {
		 al_clear_to_color(al_map_rgb(255,255,255));
         redraw = false;
		 int j=0,i=0;
		 /*for (std::vector<std::vector<std::vector<int>>>::iterator it = Map_Matrix.begin(); it != Map_Matrix.end(); ++it, j++){
			 for(std::vector<std::vector<int>>::iterator it1 = (*it).begin(); it1 != (*it).end(); ++it1, i++){
				 if((*it1)[0]==1){
					 al_draw_filled_rectangle(j*50,400-(i*50),j*50+50,400-(i*50)+50,al_map_rgb(0,0,0));

				 }
				 
			 }
			i=0;
		 }*/
		 ALLEGRO_BITMAP * tmp=al_create_bitmap(map->get_xy().first*50,map->get_xy().second*50);
		 al_set_target_bitmap(tmp);
		 al_draw_bitmap(map->get_map(),0,0,0);
		 update_players();
		 update_projectiles();

		 draw_players();
		 al_set_target_bitmap(al_get_backbuffer(display));
		 al_draw_bitmap_region(tmp,client_player->get_x()-320,165-client_player->get_y(),640,480,0,0,0);
         //al_draw_bitmap(map, 640, 480, 0);
		 
         al_flip_display();
		 al_destroy_bitmap(tmp);

      }
   }
	
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
	
}

void Game::end(){
	stop=true;

}

void Game::update_players(){
	for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
		(*it)->update();
	}
}

void Game::draw_players(){
	for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
		std::string str = (*it)->get_name();
		const char *cstr = str.c_str();
		int x=(*it)->get_x();
		int y=(*it)->get_y();
		int vx=(*it)->get_vx();
		int vy=(*it)->get_vy();
		std::string str1= "x:"+to_string(x)+" vx:"+to_string(vx);
		std::string str2= "y:"+to_string(y)+" vy:"+to_string(vy);
		const char *cstr1 = str1.c_str();
		const char *cstr2 = str2.c_str();
		al_draw_text(font, al_map_rgb(0,0,0),x, 415-y,ALLEGRO_ALIGN_CENTRE, cstr);
		al_draw_text(font, al_map_rgb(0,0,0),x, 425-y,ALLEGRO_ALIGN_CENTRE, cstr1);
		al_draw_text(font, al_map_rgb(0,0,0),x, 435-y,ALLEGRO_ALIGN_CENTRE, cstr2);

	
	}
}


void Game::add_projectile(Projectile *p){
	Projectiles.push_back(p);
	p->map_xy=map->get_xy();
}

void Game::remove_projectile(int id){
	for(list<Projectile*>::iterator it=Projectiles.begin() ; it!=Projectiles.end(); it++){
		if(id==(*it)->get_id()){
			delete (*it);
			Projectiles.erase(it);
			return;
		}

	}
}

void Game::update_projectiles(){
	for(list<Projectile*>::iterator it=Projectiles.begin() ; it!=Projectiles.end(); it++){
		(*it)->update();
	}

}

