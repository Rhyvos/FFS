#include "Map.h"
Map::Map(std::string name){
	
	std::ifstream input (name, std::ifstream::in);
	char x[1024];
	int i=0,j=0;
	
	input.getline(x,1024);
	std::stringstream buffer(x);
	buffer.getline(x,256,'\t');
	map_x=std::stoi(x);
	buffer.getline(x,256,'\t');
	map_y=std::stoi(x);
	map = al_create_bitmap((map_x)*50,(map_y)*50);
   if(!map) {
      fprintf(stderr, "failed to create map!\n");
   }
   al_set_target_bitmap(map);
 
   al_clear_to_color(al_map_rgb(255,255,255));
	std::cout<<"Building Map: "<<name<<std::endl;
	std::vector<std::vector<std::vector<int>>> Map_Matrix1(map_x,std::vector<std::vector<int>>(map_y,std::vector<int>(10)));
	Map_Matrix=Map_Matrix1;
	while(!input.eof()){
		input.getline(x,1024);
		std::stringstream buffer(x);
		while(!buffer.eof()){
			buffer.getline(x,1024,'\t');
			std::string s(x);
			if(s.compare("0")==0){
				Map_Matrix[j][i][0]=0;
				al_draw_bitmap(get_tile(s),j*50,(map_y-1)*50-(i*50),0);
			}
			else if(s.compare("1")==0){
				Map_Matrix[j][i][0]=1;
				al_draw_bitmap(get_tile(s),j*50,(map_y-1)*50-(i*50),0);
			}


				
			j++;
		}
		i++;
		j=0;
	}
}

ALLEGRO_BITMAP * Map::get_map(){
	return map;
}

void Map::add_element(int x, int y, std::string id){
	// to do stufff
}

void Map::remove_element(int x, int y){
	Map_Matrix[x][y][0]=0;
}

ALLEGRO_BITMAP * Map::get_tile(std::string id){
	std::string file_name=id+".bmp";
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "Map_Elements");
	al_set_path_filename(path, file_name.c_str());
	ALLEGRO_BITMAP * tmp = al_load_bitmap(al_path_cstr(path, '/'));
		if(tmp==NULL){
			std::cout<<"cant load:" + file_name<<std::endl;
		}

	return tmp;
}


std::pair <int,int> Map::get_xy(){
	return std::pair <int,int> (map_x,map_y);
}
