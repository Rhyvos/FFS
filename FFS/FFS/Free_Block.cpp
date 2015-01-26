#include "Free_Block.h"
#include "Map.h"
#include "Game.hpp"

Free_Block::Free_Block(int x,int y,Game *g,Map *m) : Map_Object(x,y,g,m){
	id=0;
}



void Free_Block::collision(Player *p){
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

