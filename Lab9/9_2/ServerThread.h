#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
//#include "ServerProtocol.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sstream>
#include "Reply.h"
#include "Request.h"
#include "ServerProtocolCalc.h"
using namespace std;
using namespace boost;
using namespace calculator;
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
	ServerThread(std::shared_ptr<tcp::socket> socket);
	void start();

private:
	thread myThread;
	std::shared_ptr<tcp::socket> mySocket;
};

