#include "Lobby.hpp"

using namespace std;
	Lobby::Lobby(std::string ip, std::string port):
		io_service(new boost::asio::io_service)
	{
		this->ip=ip;
		this->port=port;
		game_id=0;
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
			Players.emplace(new Player(socket,this,i++));
		}

	}

	void Lobby::remove_player(Player *p){
		cout<<"Deleting player:"<<p->get_name()<<endl;
		Players.erase(p);
		delete p;
	}

	void Lobby::create_game(std::string name, int team_size, int teams){
		std::cout<<"Creating new game: "<<name<<" Team size: "<<team_size<<" No of teams: "<<teams<<std::endl;
		Games.emplace(new Game(name,game_id,team_size,teams,this));
		game_id++;
	}


	void Lobby::send(string msg){
		for(set<Player*>::iterator it=Players.begin(); it!=Players.end() ; it++){
			(*it)->send(msg);
		}
	}

	std::list<std::string> Lobby::get_games(){
		std::list<std::string> tmp_list;
		string s;
		for (std::set<Game*>::iterator it=Games.begin(); it!=Games.end(); ++it){
			s=("game,game_list,"+(*it)->get_name()+","+std::to_string((*it)->players_number())+","+std::to_string((*it)->max_players()));
			tmp_list.emplace_back(s);
		}
		return tmp_list;
	}


	Game* Lobby::join_game(Player *p,string name){
		if(Games.size())
			for (std::set<Game*>::iterator it=Games.begin(); it!=Games.end();){
				if(!(*it)->get_name().compare(name)){
					return (*it);
				}
				it++;
			}		
		return NULL;
	}


	void Lobby::remove_game(Game* g){
		cout<<"Deleting game:"<<g->get_name()<<endl;
		Games.erase(g);
		delete g;
	}







