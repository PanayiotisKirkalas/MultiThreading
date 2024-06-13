#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <boost/asio.hpp>
#include "ServerProtocol.h"
using namespace std;
using namespace boost;
using asio::ip::tcp;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "!"
#endif // !MAXLINE

class ServerThread
{
public:
	ServerThread();
	ServerThread(std::shared_ptr <vector<tcp::socket>> sockets, int id, std::shared_ptr<recursive_mutex> lock);
	void start();

private:
	int myId;
	thread myThread;
	std::shared_ptr<recursive_mutex> lock_ptr;
	std::shared_ptr <vector<tcp::socket>> myConnections_ptr;
};

