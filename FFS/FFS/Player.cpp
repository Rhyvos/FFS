#include "Player.hpp"
#include <iostream>
#include <boost\bind.hpp>
#include <boost\thread.hpp>
#include "Lobby.hpp"

	Player::Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, Lobby* l):
		socket(socket), Movement(60)
	{
		lobby=l;
		name="unknown";
		boost::thread t(&Player::recive,this);
	}
	Player::~Player(){
		std::cout<<"Player destructor";
		socket->close();
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
				lobby->remove_player(this);
		}	
	}

	void Player::handle_recive(char *msg,std::size_t bytes_transferred){
		std::string str(msg,bytes_transferred);
		std::cout<<"["<<name<<"] "<<str;
		std::vector<std::string> split_msg=split(str,".");
		if(!split_msg[0].compare("name")){
			name.erase();
			name.insert(0,split_msg[1],0,split_msg[1].size()-2);
		}
		else if(!split_msg[0].compare("create_game")){
			lobby->create_game(split_msg[1],stoi(split_msg[2]),stoi(split_msg[3]));
		}
		else if(!split_msg[0].compare("join_game")){
			std::cout<<"3"<<std::endl;
		}
		else if(!split_msg[0].compare("leave_game")){
			std::cout<<"4"<<std::endl;
		}
		else if(!split_msg[0].compare("login")){
			std::cout<<"5"<<std::endl;
		}
		else if(!split_msg[0].compare("gamelist")){
			std::cout<<"6"<<std::endl;
		}
		else if(!split_msg[0].compare("disconnect")){
			lobby->remove_player(this);
		}
		else{
			lobby->send("["+get_name()+"] "+ str);
		}
	}

	void Player::send(std::string str){
		mtx_.lock();
		socket->send(boost::asio::buffer(str));
		mtx_.unlock();
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


	std::string Player::get_name(){
		return name;
	}
	