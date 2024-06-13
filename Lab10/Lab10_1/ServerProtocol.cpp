#include "ServerProtocol.h"

void ServerProtocol::print_message(const string& buff) {
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

string ServerProtocol::processRequest(string buff)
{
	cout << "Received message from client : " << buff << endl;
	string out = buff;
	cout << "Send message to client: " << out << endl;
	return out;
}
