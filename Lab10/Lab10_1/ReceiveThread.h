#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include "ClientProtocol.h"
using namespace std;
using namespace boost;
using asio::ip::tcp;

class ReceiveThread
{
	std::shared_ptr<tcp::socket> mySocket;
	thread myThread;
public:
	ReceiveThread();
	ReceiveThread(std::shared_ptr<tcp::socket> socket);
	void start();
	void join();
};

