#include "Lobby.hpp"



	Lobby::Lobby(int port):
		io_service(new boost::asio::io_service)
	{


	}

	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

	void Lobby::do_accept(){
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
		boost::asio::ip::tcp::acceptor acceptor(*io_service,endpoint);

	
		while (true)
		{
			socket_ptr socket(new boost::asio::ip::tcp::socket(*io_service));
			acceptor.accept(*socket);
			Players.emplace_back(socket);
		}
		

	}











