// FFS.cpp : Defines the entry point for the console application.
//



#include "Lobby.hpp"
Lobby *lobby;
int Exit(void (*stuff)(void)) {
	delete lobby;
    return 0;
}

int main()
{
	srand(std::time(NULL));
	if(!al_install_system(ALLEGRO_VERSION_INT, Exit)) {
				  fprintf(stderr, "failed to initialize allegro!\n");
				  return 0;
	}
	
	try{
	lobby= new Lobby("127.0.0.1","4444");
	boost::thread t(&Lobby::do_accept,lobby);
	t.join();
	}
	catch(std::exception &ec){
				std::cout<<"FFS: "<<ec.what()<<std::endl;

		}	
	return 0;
	
}

