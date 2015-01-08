#include "Game.hpp"
#include "Socket_session.h"


const float FPS = 60;

using namespace std;

Game::Game(Socket_session *session) : 
	session(session), display(NULL),event_queue(NULL),timer(NULL)
{
	cout<<"New game"<<endl;
	

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
	
}

void Game::remove_player(Player *p){
	Players.erase(p);
	
}

void Game::start(){
	
	redraw=true;
	if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return;
   }
 
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
			  fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
			  return ;
		   }
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return ;
   }
   al_init_primitives_addon();
   al_install_keyboard();
	
	
	al_register_event_source(event_queue,al_get_timer_event_source(timer));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_start_timer(timer);
	ALLEGRO_EVENT ev;
	
	while(true)
   {


	  al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
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
 
         
 
   
      }

      if(redraw && al_is_event_queue_empty(event_queue)) {
		 al_clear_to_color(al_map_rgb(255,255,255));
         redraw = false;
		 
		 update_players();
		 draw_players();

         

         al_flip_display();

      }
   }
	
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
}

void Game::end(){

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
		al_draw_filled_circle(x,450-y, 5, al_map_rgb(255,0,0));	
	}
}
