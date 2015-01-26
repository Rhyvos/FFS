
#include "Map.h"

Map::Map(std::string name, Game*g){
	Map_Object_Factory mof(g,this);
	std::ifstream input (name, std::ifstream::in);
	char x[1024];
	int i=0,j=0;
	input.getline(x,1024);
	std::stringstream buffer(x);
	buffer.getline(x,256,'\t');
	this->x=std::stoi(x);
	buffer.getline(x,256,'\t');
	this->y=std::stoi(x);

	std::cout<<"Building Map: "<<name<<std::endl;
	std::vector<std::vector<std::vector<Map_Object*>>> Map_Matrix1(this->x,std::vector<std::vector<Map_Object*>>(this->y,std::vector<Map_Object*>(10)));
	Map_Matrix=Map_Matrix1;
	while(!input.eof()){
		input.getline(x,1024);
		std::stringstream buffer(x);
		while(!buffer.eof()){
			buffer.getline(x,1024,'\t');
			std::string s(x);
			std::cout<<s;
			if(s.compare("0")==0)
				Map_Matrix[j][i][0]=mof.Free(j,i);
			else if(s.compare("1")==0)
				Map_Matrix[j][i][0]=mof.Solid(j,i);
			j++;
		}
		std::cout<<std::endl;
		i++;
		j=0;
	}
}

void Map::collision(Player *p){


	if(p->get_next_x()>0&&p->get_next_x()<x*50+50&&p->get_next_y()>0&&p->get_next_y()<y*50+50){
		if(Map_Matrix[(int)p->get_next_x()/50][(int)p->get_next_y()/50][0]!=NULL){
			//std::cout<<"x:"<<(int)p->get_next_x()/50<<" y:"<<(int)p->get_next_y()/50<<std::endl;
			//std::cout<<"px:"<<p->get_next_x()<<" py:"<<p->get_next_y()<<std::endl;
			Map_Matrix[(int)p->get_next_x()/50][(int)p->get_next_y()/50][0]->collision(p);
		}		
	}

		

}

void Map::collision(Projectile *p){
	if(p->get_x()>0&&p->get_x()<x*50+50&&p->get_y()>0&&p->get_y()<y*50+50){
		if(Map_Matrix[(int)p->get_x()/50][(int)p->get_y()/50][0]!=NULL){
			//std::cout<<"x:"<<(int)p->get_next_x()/50<<" y:"<<(int)p->get_next_y()/50<<std::endl;
			//std::cout<<"px:"<<p->get_next_x()<<" py:"<<p->get_next_y()<<std::endl;
			Map_Matrix[(int)p->get_x()/50][(int)p->get_y()/50][0]->collision(p);
		}		
	}
}

void Map::action(Player *p){

}

void Map::destroy_map_object(int x,int y,int z){
	if(this->x<x&&this->y<y)
	delete Map_Matrix[x][y][z];
	Map_Matrix[x][y][z]=NULL;
}

void Map::add_map_object(int x,int y,int z,Map_Object *mo){
	if(this->x<x&&this->y<y)
	Map_Matrix[x][y][z]=mo;
}

Map_Object* Map::get_map_object(int x,int y,int z){
	if(x<this->x&&y<this->y&&x>=0&&y>=0){
		return Map_Matrix[x][y][z];
	}
	else {
		return NULL;
	}
}