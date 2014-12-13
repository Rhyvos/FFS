// FFS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/asio.hpp>
#include "Lobby.hpp"
#include <boost\thread.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	Lobby lobby("127.0.0.1","4444");
	boost::thread t(&Lobby::do_accept,lobby);
	t.join();
	return 0;
	
}

