#pragma once
#include <iostream>
#include <string>
using namespace std;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "CLOSE"
#endif // !MAXLINE

class ClientProtocol
{
public:
	string prepareRequest();

	void processReply(string theInput);
};

