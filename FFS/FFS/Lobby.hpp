#ifndef LOBBY_HPP
#define LOBBY_HPP
#include <boost/asio.hpp>
#include "Player.hpp"
#include <set>

class Lobby : std::enable_shared_from_this<Lobby>{
	public:
		Lobby(std::string ip, std::string port);
		void do_accept();
		void remove_player(Player *p);
		void create_game(std::string name, int team_size, int teams);
		void join_game(Player *p);
		std::list<std::string> get_games();
		void send(std::string msg);
	private:
		std::set<Player*> Players;
		boost::shared_ptr<boost::asio::io_service> io_service;
		std::string port;
		std::string ip;
};










#endif