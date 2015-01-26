#ifndef SOCKET_SESSION_H
#define SOCKET_SESSION_H

#include "Game.hpp"

class Socket_session{

public:
	Socket_session(std::string ip,std::string port);
	~Socket_session();
	void read();
	void handle_read(char *msg,std::size_t bytes_transferred);
	void write(std::string msg);
	std::vector<std::string> split (std::string str, std::string delimiter);
	void game_msg(std::vector<std::string> msg);
	void player(std::vector<std::string> msg);
	void map(std::vector<std::string> msg);
	boost::mutex mtx_;
private:
	int player_id;
	Game *game;
	boost::asio::io_service* io_service;
	boost::asio::ip::tcp::socket* socket;
	
};


#endif