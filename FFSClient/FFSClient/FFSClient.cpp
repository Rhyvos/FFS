#include "Socket_session.h"

Socket_session *s;

int Exit(void (*stuff)(void)) {
	delete s;
    return 0;
}



int main(){

	if(!al_install_system(ALLEGRO_VERSION_INT, Exit)) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }



	s=new Socket_session("127.0.0.1","4444");
	boost::thread t(boost::bind(&Socket_session::read,s));
	
	std::string x;
	s->write("login,Gracz1,1234");
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	s->write("create_game,a,1,2");
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	s->write("join_game,a");
	while(true){
		std::cin>>x;
		s->write(x);

	}

	
	
	

	t.join();
	system("pause");
   return 0;

}