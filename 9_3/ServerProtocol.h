#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "-1"
#endif // !MAXLINE

namespace calculator {
	class ServerProtocol
	{
		unordered_map<int, double> hashTable;

		void print_message(const string& buff);
		void getRequestData(string request, int* n);
		string doServerComputation(int n);
		double f(double a);
	public:
		string processRequest(string buff);
	};
}

