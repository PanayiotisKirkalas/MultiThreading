#include "ClientProtocolCalc.h"


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

string calculator::ClientProtocol::readUserInput()
{
	string input;

	cout << "Enter message to send to server:";
	getline(cin, input);

	return input;
}

bool calculator::ClientProtocol::checkData(string data)
{
	string tokens[3];
	size_t pos = 0;

	int i;
	for (i = 0; (pos = data.find(' ')) != std::string::npos; ++i) {
		tokens[i] = data.substr(0, pos);
		data.erase(0, pos + 1);
	}
	tokens[i] = data;

	if (tokens[0].size() != 1) {
		return false;
	}
	else {
		switch (tokens[0][0])
		{
		case '+': case '-': case '*': case '/': case '!':
			break;
		default:
			return false;
		}
	}
	if (!all_of(tokens[1].begin(), tokens[1].end(), isdigit)) {
		return false;
	}
	if (!all_of(tokens[2].begin(), tokens[2].end(), isdigit)) {
		return false;
	}
	if (tokens[0][0] == '/' && stoi(tokens[2]) == 0)
		return false;

	return true;
}

string calculator::ClientProtocol::prepareRequest()
{
	bool done = false;
	string input;
	while (!done) {
		input = readUserInput();
		done = checkData(input);
		if (!done) cout << "Incorrect message" << endl;
	}
	return input;
}

void calculator::ClientProtocol::processReply(string input)
{
	cout << "Message received from server: " << input << endl;
}
