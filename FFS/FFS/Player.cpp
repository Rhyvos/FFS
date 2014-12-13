#include "Player.hpp"
#include <iostream>
#include <boost\bind.hpp>
#include <boost\thread.hpp>


	Player::Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket/*, Lobby l*/):
		socket(socket)
	{
		
		name="unknown";
		boost::thread t(&Player::recive,this);
	}

	void Player::recive(){
		char msg[MAX_MESSAGE_LENGTH];
		size_t length;
		std::cout<<"waiting for message from: "<<name<<std::endl;
		try
		{
			while (true)
			{

				length = socket->read_some(boost::asio::buffer(msg,MAX_MESSAGE_LENGTH));
				boost::thread t(boost::bind(&Player::handle_recive,this,msg,length));


			} 
		}
		catch(std::exception &ec){
				std::cout<<"["<<name<<"] "<<ec.what()<<std::endl;
		}	
	}

	void Player::handle_recive(char *msg,std::size_t bytes_transferred){
		std::string str(msg,bytes_transferred);
		std::cout<<"["<<name<<"] "<<str;
		std::vector<std::string> split_msg=split(str,".");
		if(!split_msg[0].compare("name")){
			std::cout<<"1"<<std::endl;
		}
		else if(!split_msg[0].compare("create_game")){
			std::cout<<"2"<<std::endl;
		}
		else if(!split_msg[0].compare("join_game")){
			std::cout<<"3"<<std::endl;
		}
		else if(!split_msg[0].compare("login")){
			std::cout<<"4"<<std::endl;
		}
		else if(!split_msg[0].compare("gamelist")){
			std::cout<<"5"<<std::endl;
		}
	}
	

	std::vector<std::string> Player::split (std::string str, std::string delimiter){
		std::vector<std::string> tmp;
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			tmp.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		tmp.push_back(str);
		return tmp;
	}

	