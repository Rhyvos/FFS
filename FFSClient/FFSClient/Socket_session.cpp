#include "Socket_session.h"

using namespace std;

#define MAX_MESSAGE_LENGTH 1024






Socket_session::Socket_session(string ip, string port): 
	io_service(new boost::asio::io_service), 
	socket(new boost::asio::ip::tcp::socket(*io_service)),
	game(NULL)
{
	try
	{
		boost::asio::ip::tcp::resolver resolver( *io_service );
		boost::asio::ip::tcp::resolver::query query( ip,port);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
		std::cout << "Connecting"<< std::endl;


		boost::asio::connect(*socket, iterator);

		

		
	}
	catch(std::exception e){
		cout<<"Failed at: "<<e.what()<<endl;
		if(socket->is_open())
			socket->close();
		return;
	}

}

Socket_session::~Socket_session(){
	delete game;
	delete io_service;
	delete socket;
}



void Socket_session::read(){
	char msg[MAX_MESSAGE_LENGTH];
		size_t length;
		try
		{
			while (true)
			{

				length = socket->read_some(boost::asio::buffer(msg,MAX_MESSAGE_LENGTH));
				boost::thread t(boost::bind(&Socket_session::handle_read,this,msg,length));


			} 
		}
		catch(std::exception &ec){
				std::cout<<ec.what()<<std::endl;
				return;
		}	

}


void Socket_session::handle_read(char *msg,std::size_t bytes_transferred){
	mtx_.lock();
	std::string str(msg,bytes_transferred);
	std::vector<std::string> split_msg=split(str,",");
	str=str.substr(0,str.size()-1);
	cout<<str<<endl;
	if(!split_msg[0].compare("game")){
		game_msg(split_msg);
	}else if(!split_msg[0].compare("player")){
		player(split_msg);
	}else if(!split_msg[0].compare("map")){
		map(split_msg);
	}else if(!split_msg[0].compare("error")){

	}
	mtx_.unlock();


	



}

void Socket_session::game_msg(std::vector<std::string> msg){
	if(!msg[1].compare("start")&&game!=NULL){
		cout<<msg[0]<<" "<<msg[1]<<endl;
		boost::thread t(boost::bind(&Game::start,game));
	}else if(!msg[1].compare("end")&&game!=NULL){
		game->end();
	}else if(!msg[1].compare("create")){
		game=new Game(this);
		game->player_id=player_id;
	}else if(!msg[1].compare("game_list")){
		cout<<"Game: "<<msg[2]<<" Players:"<<msg[3]<<"/"<<msg[2]<<endl;
	}else if(!msg[1].compare("join_game")&&game!=NULL){
		Player *p=new Player(msg[2],stoi(msg[3]),game);
		game->add_player(p);
	}else if(!msg[1].compare("leave_game")&&game!=NULL){
		Player *p = game->find_player(stoi(msg[2]));
		if(p!=NULL){
			game->remove_player(p);
		}
	}else if(!msg[1].compare("your_id")){
		player_id=stoi(msg[2]);
	}else if(!msg[1].compare("add_projectile")&&game!=NULL){
		Projectile *p=new Projectile(stoi(msg[2]),stof(msg[3]),stof(msg[4]),stof(msg[5]));
		game->add_projectile(p);
	}else{
		cout<<msg[0]<<"--"<<msg[1]<<endl;
	}


}


void Socket_session::player(std::vector<std::string> msg){
	Player *p = game->find_player(stoi(msg[1]));
	if(p!=NULL){
		p->read_msg(msg);
	}
}

void Socket_session::map(std::vector<std::string> msg){

}



std::vector<std::string> Socket_session::split (std::string str, std::string delimiter){
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

void Socket_session::write(string msg)
  {

	  mtx_.lock();
		try{
			socket->send(boost::asio::buffer(msg+"\n"));
		}
		catch(std::exception &ec){
				std::cout<<ec.what()<<std::endl;
				boost::this_thread::sleep(boost::posix_time::milliseconds(300));
				socket->close();
		}
		mtx_.unlock();
  }