#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include "Request.h"
#include "Reply.h"
using namespace std;

namespace calculator {

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "!"
#endif // !MAXLINE

	class ClientProtocol
	{
		string readUserInput();
		Request check_prepareData(string data);
	public:
		Request prepareRequest();
		void processReply(Reply input);
		void print_message(const string& buff, size_t len);
	};
}

