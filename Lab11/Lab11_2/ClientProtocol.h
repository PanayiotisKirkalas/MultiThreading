#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

namespace calculator {

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE -1
#endif // !MAXLINE

	class ClientProtocol
	{
		void print_message(const string& buff);
		int readUserInput();
	public:
		int prepareRequest();
		void processReply(double input);
	};
}

