#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "Sum.h"
using namespace std;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "CLOSE"
#endif // !MAXLINE

class ServerProtocol
{
	int myId, myInit;
	void print_message(const string& buff);
public:
	ServerProtocol(int init, int id);
	string prepareRequest();
	double processReply(string input);
};

