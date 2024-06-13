#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <mutex>
#include "WorkerThread.h"
using namespace std;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "-1"
#endif // !MAXLINE
#define numWorkers 4

class ClientProtocol {
	void print_message(const string& buff);
public:
	string compute(string request);
};

