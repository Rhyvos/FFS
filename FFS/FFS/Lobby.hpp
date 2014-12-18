#ifndef LOBBY_HPP
#define LOBBY_HPP
#include <boost/asio.hpp>
#include "Player.hpp"
#include "Game.hpp"
#include <set>

class Lobby : std::enable_shared_from_this<Lobby>{
	public:
		Lobby(std::string ip, std::string port);
		void do_accept();
		void remove_player(Player *p);
		void create_game(std::string name, int team_size, int teams);
		Game* join_game(Player *p, std::string name);
		std::list<std::string> get_games();
		void send(std::string msg);
		void remove_game(Game* g);
	private:
		std::set<Game*> Games;
		std::set<Player*> Players;
		boost::shared_ptr<boost::asio::io_service> io_service;
		std::string port;
		std::string ip;
		int game_id;
};










#endif