#include "Lobby.hpp"
#include <iostream>
using namespace std;
	Lobby::Lobby(std::string ip, std::string port):
		io_service(new boost::asio::io_service)
	{
		this->ip=ip;
		this->port=port;
	}

	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

	void Lobby::do_accept(){

		boost::asio::ip::tcp::resolver resolver( *io_service );
		boost::asio::ip::tcp::resolver::query query( ip,port);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
		boost::asio::ip::tcp::endpoint endpoint = *iterator;


		std::cout << "Connecting to: " << endpoint << std::endl;


		boost::asio::ip::tcp::acceptor acceptor(*io_service,endpoint);
		std::cout<<"waiting for connection"<<std::endl;
		int i=0;
		while (true)
		{
			socket_ptr socket(new boost::asio::ip::tcp::socket(*io_service));
			acceptor.accept(*socket);
			Players.emplace(new Player(socket,this));
		}


		

	}

	void Lobby::remove_player(Player *p){
		cout<<"Deleting player:"<<p->get_name()<<endl;
		Players.erase(p);
	}

	void Lobby::create_game(std::string name, int team_size, int teams){
		std::cout<<"Creating new game: "<<name<<" Team size: "<<team_size<<" No of teams: "<<teams<<std::endl;
	}










