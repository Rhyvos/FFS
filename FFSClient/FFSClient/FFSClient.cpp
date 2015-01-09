#include "Socket_session.h"

int main(){
	Socket_session *s=new Socket_session("127.0.0.1","4444");
	boost::thread t(boost::bind(&Socket_session::read,s));
	
	std::string x;
	s->write("login,Gracz1,1234");
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	s->write("create_game,a,1,1");
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