#include "Free_Block.h"

void Free_Block::collision(Player *p){
	p->fall();
}

void Free_Block::collision(Projectile *p){
	for(std::set<Player *>::iterator it=Players.begin();it!=Players.end();it++){
		if((*it)->get_x()-p->get_x()>-25 && (*it)->get_x()-p->get_x()<25 && (*it)->get_y()-p->get_y()>0 && (*it)->get_y()-p->get_y()<100){
			std::cout<<"Collision"<<std::endl;

		}

	}

}

void Free_Block::action(Player *p){

}

