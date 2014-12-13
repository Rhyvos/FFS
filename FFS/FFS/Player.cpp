#include "Player.hpp"

	Player::Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket):
		socket(socket)
	{


	}