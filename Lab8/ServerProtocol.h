#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#ifndef MAXLINE
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 5 /*maximum number of waiting client connections */
#define EXITMESSAGE "!"
#endif // !MAXLINE

namespace msg_modification {
	class ServerProtocol
	{
		void print_message(const string& buff) {
			bool flag = false;
			for (int i = 0; i < MAXLINE && !flag; ++i) {
				if (buff[i] == ' ')
					cout << '_';
				else if (buff[i] == '\n')
					cout << "\\n";
				else if (buff[i] == '\0') {
					cout << "\\0";
					flag = true;
				}
				else
					cout << buff[i];
			}
			cout << endl;
		}

		void decrypt(string& buff, int offset);

		void encrypt(string& buff, int offset);

		void to_uppercase(string& buff);

		void to_lowercase(string& buff);

	public:
		string processRequest(char buff[MAXLINE]);
	};
}

