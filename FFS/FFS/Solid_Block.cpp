#include "Solid_Block.h"
#include "Map.h"
#include "Game.hpp"


Solid_Block::Solid_Block(int x,int y,Game *g,Map *m) : Map_Object(x,y,g,m){
	id=1;
}


void Solid_Block::collision(Player *p){

	
	Map_Object * m=map->get_map_object(p->get_x()/50,p->get_y()/50,0);	
	std::pair <int,int> a=m->get_xy();
	std::pair <int,int> b=get_xy();
	int loc_x=a.first-b.first;
	int loc_y=a.second-b.second;
	float new_x, new_y;
	if(loc_x==1||loc_x==-1){
		if(loc_y==0){

			new_x=(((int)p->get_x()/50)*50);
			new_y=p->get_next_y();
			if(loc_x==-1){
				new_x+=49;
			}
			p->move_to(new_x,new_y);
			p->instant_stop_x();
			game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
		}else if(loc_y==1||loc_y==-1){
			new_x=(((int)p->get_x()/50)*50);
			new_y=(((int)p->get_y()/50)*50);
			if(loc_y==-1){
				new_y+=49;
			}
			if(loc_x==-1){
				new_x+=49;
			}
		}



	}else if(loc_x==0){
		if(loc_y==0){
			if(p->get_x()-(x*50)>2&&p->get_x()-(x*50)<48)
			if(p->get_x()-(x*50)>25){
				p->move_to((x+1)*50,p->get_y());
				p->instant_stop_x();
				game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
			}else {
				p->move_to((x)*50-1,p->get_y());
				p->instant_stop_x();
				game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
			}
			if(p->get_y()-(y*50)>2&&p->get_y()-(y*50)<48)
			if(p->get_y()-(y*50)>25){
				p->move_to(p->get_x(),(y+1)*50);
				p->instant_stop_y();
				game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
			}else {
				p->move_to(p->get_x(),(y)*50-1);
				p->instant_stop_y();
				game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
			}






		}else if(loc_y==1||loc_y==-1){

			new_y=(((int)p->get_y()/50)*50);
			new_x=p->get_next_x();
			if(loc_y==-1){
				new_y+=49;
			}
			p->move_to(new_x,new_y);
			p->instant_stop_y();
			game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());

		}
	}





	/*if(p->get_vy()<0){
		p->move_to(p->get_x(),y*50+50);
		p->instant_stop_y();
		std::cout<<"Solid_Block::collision v<0"<<std::endl;
		game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
	}	
	else if(p->get_next_y()+100>y*50+50){
		p->move_to(p->get_next_x(),y*50-1);
		p->instant_stop_y();
		game->send("player,"+p->get_id()+",instant_stop_y,"+p->get_string_x()+","+p->get_string_y());
	}

	Map_Object * m1=map->get_map_object(x+1,y,0);	
	Map_Object * m2=map->get_map_object(x-1,y,0);	
	std::cout<<"found"<<std::endl;
	if((m1!=NULL)?m1->get_id()==1:false&&(m1!=NULL)?m2->get_id()==1:false){
			if(p->get_vx()<0){
				p->move_to(x*50+50,p->get_y());
				p->instant_stop_x();
				std::cout<<"vx<0"<<std::endl;
				game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
			}
			else {
				std::cout<<"vx>0"<<std::endl;
				if(x>0)
					p->move_to(x*50-1,p->get_next_y());
				else
					p->move_to(x*50+50,p->get_next_y());
				p->instant_stop_x();
				game->send("player,"+p->get_id()+",instant_stop_x,"+p->get_string_x()+","+p->get_string_y());
	}*/
	//}
	p->update();
		
}

void Solid_Block::collision(Projectile *p){
		game->remove_projectile(p);
}

void Solid_Block::action(Player *p){

}
