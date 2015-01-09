#ifndef PLAYER_HPP
#define PLAYER_HPP
 


#include "Movement.hpp"	
class Lobby;
class Game;
class Player : public Movement{
	public:
		enum { MAX_MESSAGE_LENGTH = 1024 };
		Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, Lobby* l, int id);
		~Player();
		void send(std::string str);
		void handle_send(const boost::system::error_code& error);
		void recive(); 
		void handle_lobby_recive(char *msg,std::size_t bytes_transferred);
		void handle_game_recive(char *msg,std::size_t bytes_transferred);
		void set_name(std::string str);
		std::vector<std::string> split (std::string str,std::string delimiter);
		std::string get_name();
		bool in_game;
		void set_team(int i);
		void end_game();
		void login(std::string name, std::string pw);
		std::string get_id();
	private:
		int team;
		int id;
		boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
		std::string name;
		Lobby *lobby;
		Game *game;
		boost::mutex mtx_;
		bool logged;
		
};

#endif