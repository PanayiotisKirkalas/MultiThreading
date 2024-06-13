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

ServerProtocol::ServerProtocol(int init, int id)
	:myId(id), myInit(init) {}

string ServerProtocol::prepareRequest()
{
	string out = to_string(myInit) + " " + to_string(myId);
	cout << "Send message to client: " << out << endl;
	return out;
}

double ServerProtocol::processReply(string input)
{
	double val = stod(input);
	return val;
}
