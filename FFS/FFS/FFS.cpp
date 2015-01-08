// FFS.cpp : Defines the entry point for the console application.
//



#include "Lobby.hpp"


int main()
{
	try{
	Lobby lobby("127.0.0.1","4444");
	boost::thread t(&Lobby::do_accept,lobby);
	t.join();
	}
	catch(std::exception &ec){
				std::cout<<"FFS: "<<ec.what()<<std::endl;

		}	
	return 0;
	
}

