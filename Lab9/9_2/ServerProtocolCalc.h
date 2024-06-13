#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "Request.h"
#include "Reply.h"
using namespace std;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "!"
#endif // !MAXLINE

namespace calculator {
	class ServerProtocol
	{
		void getRequestData(string request, char* op, float* a, float* b);
		string doServerComputation(char op, float a, float b);
	public:
		void print_message(const string& buff);
		Reply processRequest(Request req);
	};
}

