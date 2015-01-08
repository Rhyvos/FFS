#include "Player.hpp"
#include "Lobby.hpp"
#include "Bullet.hpp"

using namespace std;

	Player::Player(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, Lobby* l, int id):
		socket(socket), Movement(60)
	{
		lobby=l;
		name="unknown";
		boost::thread t(&Player::recive,this);
		in_game=false;
		game=NULL;
		logged=false;
		this->id=id;
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
		std::vector<std::string> split_msg=split(str,",");
		str=str.substr(0,str.size()-1);
		cout<<str<<endl;
		if(!logged){
			if(!split_msg[0].compare("login"))
				login(split_msg[1],split_msg[2]);


		}else if(!split_msg[0].compare("name")){
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
			if(g!=NULL&&g->players_number()<g->max_players()){
				game=g;
				game->add_player(this);
			}
			else
				send("error,couldn't find game:"+split_msg[1]+" or game is full");
		}
		else if(!split_msg[0].compare("leave_game")){
			if(game!=NULL){
				game->remove_player(this);
				game=NULL;
			}	
			else
				send("error,no game");
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
		std::vector<std::string> split_msg=split(str,",");
		str=str.substr(0,str.size()-1);
		cout<<str<<endl;

		if(!split_msg[0].compare("disconnect")){
			lobby->remove_player(this);
		}
		else if(!split_msg[0].compare("start_move")){
			boost::thread t(boost::bind(&Movement::start_move,this,stof(split_msg[1])));
			game->send("player,"+to_string(id)+","+split_msg[0]+","+split_msg[1]+","+this->get_string_x()+","+this->get_string_y());
		}
		else if(!split_msg[0].compare("jump")){
			cout<<"jump"<<endl;
			boost::thread t(boost::bind(&Movement::jump,this,stof(split_msg[1])));
			game->send("player,"+to_string(id)+","+split_msg[0]+","+split_msg[1]+","+this->get_string_x()+","+this->get_string_y());
		}
		else if(!split_msg[0].compare("stop_move")){
			boost::thread t(boost::bind(&Movement::stop_move,this));
			game->send("player,"+to_string(id)+","+split_msg[0]+","+split_msg[1]+","+this->get_string_x()+","+this->get_string_y());
		}
		else if(!split_msg[0].compare("shoot")){			/*       No Scripted       */
			game->add_projectile(new Bullet(this->get_x(), this->get_y(),stof(split_msg[1]), this->team ));
			game->send("player,"+to_string(id)+",shoot,"+this->get_string_x()+","+this->get_string_y()+","+split_msg[1]);
		}
		else if(!split_msg[0].compare("swap_weapon")){		/*       No Scripted       */
			cout<<"["<<name<<"] action"<<endl;
		}
		else if(!split_msg[0].compare("action")){			/*       No Scripted       */
			cout<<"["<<name<<"] action"<<endl;
		}
		else{
			lobby->send("["+get_name()+"] "+ str);	
		}
	}




	void Player::send(std::string str){
		mtx_.lock();
		cout<<str<<endl;
		try{
			socket->send(boost::asio::buffer(str+"\n"));
		}
		catch(std::exception &ec){
				std::cout<<"["<<name<<"] "<<ec.what()<<std::endl;
				boost::this_thread::sleep(boost::posix_time::milliseconds(300));
				lobby->remove_player(this);
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
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
		
		tmp.push_back(str.substr(0,str.size()-1));
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

	void Player::login(string name,string pw){
		/*       No Scripted       */
		cout<<name<<" "<<pw<<endl;
		this->name.erase();
		this->name.insert(0,name,0,name.size());
		this->logged=true;
		
	}

	string Player::get_id(){
		return to_string(id);
	}
