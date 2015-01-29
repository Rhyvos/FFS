#include "Free_Block.h"
#include "Map.h"
#include "Game.hpp"

Free_Block::Free_Block(int x,int y,Game *g,Map *m) : Map_Object(x,y,g,m){
	id=0;
}



void Free_Block::collision(Player *p){
	if(p->get_vx()<0){
		Map_Object * m1=map->get_map_object((p->get_next_x()-25)/50,p->get_next_y()/50,0);
		Map_Object * m2=map->get_map_object((p->get_next_x()-25)/50,(p->get_next_y()+50)/50,0);
		

		if((m1!=NULL)?m1->get_id()==1:false){
			p->move_to((m1->get_xy().first+1)*50+25,p->get_y());
			p->instant_stop_x();
			game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
		}
		if((m2!=NULL)?m2->get_id()==1:false){
			p->move_to((m1->get_xy().first+1)*50+25,p->get_y());
			p->instant_stop_x();
			game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
		}

	}else {

		Map_Object * m1=map->get_map_object((p->get_next_x()+25)/50,p->get_next_y()/50,0);
		Map_Object * m2=map->get_map_object((p->get_next_x()+25)/50,(p->get_next_y()+50)/50,0);
		if((m1!=NULL)?m1->get_id()==1:false){
			p->move_to((m2->get_xy().first)*50-26,p->get_y());
			p->instant_stop_x();
			game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
		}
		if((m2!=NULL)?m2->get_id()==1:false){
			p->move_to((m2->get_xy().first)*50-26,p->get_y());
			p->instant_stop_x();
			game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
		}

	}


	if(p->get_vy()>0){
		Map_Object * m1=map->get_map_object((p->get_next_x()+25)/50,(p->get_next_y()+75)/50,0);
		Map_Object * m2=map->get_map_object((p->get_next_x()-25)/50,(p->get_next_y()+75)/50,0);
		if((m1!=NULL)?m1->get_id()==1:false){
			p->move_to(p->get_x(),m1->get_xy().second*50-76);
			p->instant_stop_y();
			game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
		}
		if((m2!=NULL)?m2->get_id()==1:false){
			p->move_to(p->get_x(),m2->get_xy().second*50-76);
			p->instant_stop_y();
			game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
		}
	}




	if(p->get_next_y()>y*50){
		if(!p->is_falling()){
			p->fall();
			game->send("player,"+p->get_id()+",fall,"+p->get_string_x()+","+p->get_string_y());
		}

		
	}else {
		Map_Object * mo=map->get_map_object(x,y-1,0);
		if(mo!=NULL){
			if(mo->get_id()==0)
				if(!p->is_falling()){
					p->fall();
					game->send("player,"+p->get_id()+",fall,"+p->get_string_x()+","+p->get_string_y());
				}
		}


			
	}
	p->update();
}

void Free_Block::collision(Projectile *p){
	p->update();
}

void Free_Block::action(Player *p){

}

