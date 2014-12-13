#ifndef LOBBY_HPP
#define LOBBY_HPP

#include <boost/asio.hpp>
#include "Player.hpp"

using namespace std;

class Lobby{
	public:
		Lobby(int port);
		void do_accept();



	private:
		list<Player> Players;
		boost::shared_ptr<boost::asio::io_service> io_service;
		int port;
};










#endif