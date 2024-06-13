#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "ServerProtocol.h"
#include "Sum.h"
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
	ServerThread(std::shared_ptr<tcp::socket> socket, int id, Sum* sum);
	void start();
	void join();

private:
	int myID;
	Sum* sum_ptr;
	thread myThread;
	std::shared_ptr<tcp::socket> mySocket;
};

