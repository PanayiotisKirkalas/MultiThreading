#include "ClientProtocol.h"


void calculator::ClientProtocol::print_message(const string& buff) {
	bool flag = false;
	for (int i = 0; i < buff.size() + 1; ++i) {
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

int calculator::ClientProtocol::readUserInput()
{
	int input;

	cout << "Enter message to send to server:";
	cin >> input;

	return input;
}

int calculator::ClientProtocol::prepareRequest()
{
	bool done = false;
	int input;
	input = readUserInput();
	return input;
}

void calculator::ClientProtocol::processReply(double input)
{
	cout << "Message received from server: " << input << endl;
}
