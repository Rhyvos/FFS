#ifndef PLAYER_HPP
#define PLAYER_HPP
 
#include <boost/asio.hpp>



class Player{
	public:
		enum { MAX_MESSAGE_LENGTH = 1024 };
		Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket/*, Lobby l*/);
		void send(std::string str);
		void recive();
		void handle_recive(char *msg,std::size_t bytes_transferred);
		void set_name(std::string str);
		std::vector<std::string> split (std::string str,std::string delimiter);

	private:
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
		std::string name;
		//Lobby *lobby;
};

#endif