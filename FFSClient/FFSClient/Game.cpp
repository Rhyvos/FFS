#include "Game.hpp"
#include "Socket_session.h"

#define PI 3.14159265
const float FPS = 60;

using namespace std;

Game::Game(Socket_session *session) : 
	session(session), display(NULL),event_queue(NULL),timer(NULL)
{
	cout<<"New game"<<endl;
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
   al_init_primitives_addon();
   al_install_keyboard();
	al_install_mouse();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_timer_event_source(timer));
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_start_timer(timer);
	ALLEGRO_EVENT ev;
	create_map("Map1.txt");
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
				int y=(float)(450-ev.mouse.y)-client_player->get_y();
				float alpha=atan2 (y,x) * 180 / PI;
				session->write("shoot,"+to_string(alpha));
		  }

				
	  }

      if(redraw && al_is_event_queue_empty(event_queue)) {
		 al_clear_to_color(al_map_rgb(255,255,255));
         redraw = false;
		 
		  
		 for(int i=50;i<=600;i+=50){
			 al_draw_line( i, 0, i, 480, al_map_rgb(128,128,0),1); 
		 }
		 for(int i=50;i<=450;i+=50){
			 al_draw_line( 0, i, 640, i, al_map_rgb(128,128,0),1); 
		 }
		 update_players();
		 update_projectiles();
		 draw_players();
		 
         al_draw_bitmap(map, 640, 480, 0);

         al_flip_display();

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

void Game::create_map(std::string name){


	map = al_create_bitmap(640,480);
   if(!map) {
      fprintf(stderr, "failed to create map!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return;
   }
 
   al_set_target_bitmap(map);
 
   al_clear_to_color(al_map_rgb(0,0,128));
 
	al_draw_filled_rectangle(0,450,600,400,al_map_rgb(0,0,0));

	std::ifstream input (name, std::ifstream::in);
	char x[1024];
	int i=0,j=0;
	int map_x,map_y;
	input.getline(x,1024);
	std::stringstream buffer(x);
	buffer.getline(x,256,'\t');
	map_x=std::stoi(x);
	buffer.getline(x,256,'\t');
	map_y=std::stoi(x);

	std::cout<<"Building Map: "<<name<<std::endl;
	std::vector<std::vector<std::vector<int>>> Map_Matrix1(map_x,std::vector<std::vector<int>>(map_y,std::vector<int>(10)));
	Map_Matrix=Map_Matrix1;
	while(!input.eof()){
		input.getline(x,1024);
		std::stringstream buffer(x);
		while(!buffer.eof()){
			buffer.getline(x,1024,'\t');
			std::string s(x);
			std::cout<<s;
			if(s.compare("0")==0){
				Map_Matrix[j][i][0]=0;
				al_draw_filled_rectangle(j*50,450-(i*50),j*50+50,450-(i*50)+50,al_map_rgb(255,255,255));
			}
			else if(s.compare("1")==0){
				Map_Matrix[j][i][0]=1;
				al_draw_filled_rectangle(j*50,450-(i*50),j*50+50,450-(i*50)+50,al_map_rgb(0,0,0));
			}


				
			j++;
		}
		std::cout<<std::endl;
		i++;
		j=0;
	}

	al_set_target_bitmap(al_get_backbuffer(display));

}
