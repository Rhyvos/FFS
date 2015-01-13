#ifndef GAME_H	
#define GAME_H
#include "Player.hpp"
#include "Projectile.hpp"
class Lobby;

class Game{
	public:
		Game(std::string name,int id,int team_size, int teams, Lobby* l);
		~Game();
		std::string get_name();

		void add_player(Player* p);
		void remove_player(Player* p);
		void start();
		void game_end();
		void send(std::string msg);

		int players_number();
		int max_players();

		Game* get_game();

		void collisions(Player* p);
		void add_projectile(Projectile* p);


	private:
		Lobby* lobby;
		std::set<Player*> Players;
		std::list<Projectile*> Projectiles;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_TIMER *timer;
		void update();
		void build_map();
		void start_players();
		const int id;
		const std::string name;
		int team_size; 
		int teams;
		int time;
		bool running;
};





#endif