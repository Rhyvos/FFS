#ifndef MAP_H
#define MAP_H
#include "Headers.h"
class Map{
public:
	Map(std::string name);
	ALLEGRO_BITMAP * get_map();
	void add_element(int x, int y, std::string id);
	void remove_element(int x, int y);
	std::pair <int,int> get_xy();
private:
	int map_x,map_y;
	ALLEGRO_BITMAP * get_tile(std::string id);
	ALLEGRO_BITMAP * map;
	std::vector<std::vector<std::vector<int>>> Map_Matrix;
};




#endif // !MAP_H
