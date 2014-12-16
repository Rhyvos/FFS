#ifndef PLAYER_HPP
#define PLAYER_HPP
 
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include "Movement.hpp"	
class Lobby;

class Player : public Movement{
	public:
		enum { MAX_MESSAGE_LENGTH = 1024 };
		Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, Lobby* l);
		~Player();
		void send(std::string str);
		void handle_send(const boost::system::error_code& error);
		void recive(); 
		void handle_recive(char *msg,std::size_t bytes_transferred);
		void set_name(std::string str);
		std::vector<std::string> split (std::string str,std::string delimiter);
		std::string get_name();
	private:
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
		std::string name;
		Lobby *lobby;
		boost::mutex mtx_;
};

#endif