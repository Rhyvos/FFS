#ifndef PLAYER_HPP
#define PLAYER_HPP
 
#include <boost/asio.hpp>


class Player{
	public:
		Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);






	private:
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
};







#endif