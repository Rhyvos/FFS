#include "Player.hpp"
#include <iostream>
#include <boost\bind.hpp>
#include <boost\thread.hpp>
#include "Lobby.hpp"

using namespace std;

	Player::Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, Lobby* l):
		socket(socket), Movement(60)
	{
		lobby=l;
		name="unknown";
		boost::thread t(&Player::recive,this);
		in_game=false;
		game=NULL;
	}
	Player::~Player(){
		if(game!=NULL)
			game->remove_player(this);
		socket->close();
	}




	void Player::recive(){
		char msg[MAX_MESSAGE_LENGTH];
		size_t length;
		try
		{
			while (true)
			{

				length = socket->read_some(boost::asio::buffer(msg,MAX_MESSAGE_LENGTH));
				if(!in_game)
					boost::thread t(boost::bind(&Player::handle_lobby_recive,this,msg,length));
				else 
					boost::thread t(boost::bind(&Player::handle_game_recive,this,msg,length));


			} 
		}
		catch(std::exception &ec){
				std::cout<<"["<<name<<"] "<<ec.what()<<std::endl;
				boost::this_thread::sleep(boost::posix_time::milliseconds(300));
				lobby->remove_player(this);
		}	
	}

	void Player::handle_lobby_recive(char *msg,std::size_t bytes_transferred){
		std::string str(msg,bytes_transferred);
		std::vector<std::string> split_msg=split(str,".");
		if(!split_msg[0].compare("name")){
			name.erase();
			name.insert(0,split_msg[1],0,split_msg[1].size());
		}
		else if(!split_msg[0].compare("create_game")){
			lobby->create_game(split_msg[1],stoi(split_msg[2]),stoi(split_msg[3]));
		}
		else if(!split_msg[0].compare("join_game")){
			Game* g=lobby->join_game(this,split_msg[1]);
			if(game!=NULL){
				game->remove_player(this);
				game=NULL;
			}
			if(g!=NULL){
				game=g;
				game->add_player(this);
			}
			else
				send("error.couldn't find game:"+split_msg[1]+"\n");
		}
		else if(!split_msg[0].compare("leave_game")){
			if(game!=NULL){
				game->remove_player(this);
				game=NULL;
			}	
			else
				send("error.no game\n");
		}
		else if(!split_msg[0].compare("login")){
			std::cout<<"Login function (not scripted)\n"<<std::endl;
		}
		else if(!split_msg[0].compare("gamelist")){
			std::list<std::string> tmp=lobby->get_games();
			for (std::list<std::string>::iterator it=tmp.begin(); it!=tmp.end(); ++it){
				this->send((*it));
			}
		}
		else if(!split_msg[0].compare("disconnect")){
			lobby->remove_player(this);
		}
		else{
			if(game==NULL){
				lobby->send("["+get_name()+"] "+ str);
			}
			else{
				game->send("["+get_name()+"] "+ str);
			}
		}
	}



	void Player::handle_game_recive(char *msg,std::size_t bytes_transferred){
		std::string str(msg,bytes_transferred);
		std::vector<std::string> split_msg=split(str,".");
		if(!split_msg[0].compare("disconnect")){
			lobby->remove_player(this);
		}
		else if(!split_msg[0].compare("start_move")){
			boost::thread t(boost::bind(&Movement::start_move,this,stof(split_msg[1].replace(split_msg[1].find(","),1,".",1))));
			game->send("player."+name+"."+str);
		}
		else if(!split_msg[0].compare("jump")){
			cout<<"jump"<<endl;
			boost::thread t(boost::bind(&Movement::jump,this,std::stof(split_msg[1].replace(split_msg[1].find(","),1,".",1))));
			game->send("player."+name+"."+str);
		}
		else if(!split_msg[0].compare("stop_move")){
			boost::thread t(boost::bind(&Movement::stop_move,this));
			game->send("player."+name+"."+str);
		}
		else if(!split_msg[0].compare("shoot")){
			cout<<"["<<name<<"] action"<<endl;
		}
		else if(!split_msg[0].compare("swap_weapon")){
			cout<<"["<<name<<"] action"<<endl;
		}
		else if(!split_msg[0].compare("action")){
			cout<<"["<<name<<"] action"<<endl;
		}
		else{
			lobby->send("["+get_name()+"] "+ str);
		}
	}




	void Player::send(std::string str){
		mtx_.lock();
		try{
			socket->send(boost::asio::buffer(str));
		}
		catch(std::exception &ec){
				std::cout<<"["<<name<<"] "<<ec.what()<<std::endl;
				boost::this_thread::sleep(boost::posix_time::milliseconds(300));
				lobby->remove_player(this);
		}
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
		
		tmp.push_back(str.substr(0,str.size()-2));
		return tmp;
	}


	std::string Player::get_name(){
		return name;
	}
	
	void Player::set_team(int i){
		team=i;
	}

	void Player::end_game(){
		in_game=false;
		game=NULL;
	}