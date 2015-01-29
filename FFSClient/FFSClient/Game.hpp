#ifndef GAME_HPP
#define GAME_HPP

#include "Player.h"
#include "Projectile.h"
#include "Map.h"

class Socket_session;

class Game{
public:
	Game(Socket_session *session);
	~Game();
	void start();
	void end();
	void add_player(Player *p);
	void remove_player(Player *p);
	Player * find_player(int id);
	Player * find_player(std::string name);
	void add_projectile(Projectile *p);
	void remove_projectile(int id);
	void create_map(std::string map_name);
	void update_projectiles();
	void update_players();
	void draw_players();
	void draw_prtojectiles();
	int player_id;
	
private:
	std::vector<std::vector<std::vector<int>>> Map_Matrix;
	std::set<Player *> Players;
	Player * client_player;
	std::list<Projectile *> Projectiles;
	Socket_session *session;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;
	bool redraw;
	bool stop;
	Map *map;
};


#endif