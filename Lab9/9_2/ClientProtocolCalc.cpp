#include "ClientProtocolCalc.h"


void calculator::ClientProtocol::print_message(const string& buff, size_t len) {
	cout << "Size: " << buff.size() << endl;
	for (int i = 0; i < buff.size() + 1; ++i) {
		if (buff[i] == ' ')
			cout << '_ ';
		else if (buff[i] == '\n')
			cout << "\\n ";
		else if (buff[i] == '\0') {
			cout << "\\0 ";
		}
		else
			cout << (buff[i]) << ' ';
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

Request calculator::ClientProtocol::check_prepareData(string data)
{
	string tokens[3];
	float num1, num2;
	size_t pos = 0;

	int i;
	for (i = 0; (pos = data.find(' ')) != std::string::npos; ++i) {
		tokens[i] = data.substr(0, pos);
		data.erase(0, pos + 1);
	}
	tokens[i] = data;

	if (tokens[0].size() != 1) {
		//cout << "Size: " << tokens[0].size() << endl;
		return Request("ERR", -9999, -9999);
	}
	else {
		switch (tokens[0][0])
		{
		case '+':
			tokens[0] = "ADD";
			break;
		case '-': 
			tokens[0] = "SUB";
			break;
		case '*': 
			tokens[0] = "MUL";
			break;
		case '/': 
			tokens[0] = "DIV";
			break;
		case '!':
			return Request("!", -9999, -9999);
		default:
			return Request("ERR", -9999, -9999);
		}
	}
	if (!all_of(tokens[1].begin(), tokens[1].end(), isdigit)) {
		cout << "check 1" << endl;
		return Request("ERR", -9999, -9999);
	}
	num1 = stof(tokens[1]);
	if (!all_of(tokens[2].begin(), tokens[2].end(), isdigit)) {
		cout << "check 2" << endl;
		return Request("ERR", -9999, -9999);
	}
	if (tokens[0][0] == '/' && stoi(tokens[2]) == 0) {
		cout << "check 3" << endl;
		return Request("ERR", -9999, -9999);
	}
	num2 = stof(tokens[2]);

	return Request(tokens[0], num1, num2);
}

Request calculator::ClientProtocol::prepareRequest()
{
	bool done = false;
	string input;
	Request request;
	do {
		input = readUserInput();
		request = check_prepareData(input);
		if (request.getOpcode()._Equal("ERR")) cout << "Incorrect message" << endl;
	} while (request.getOpcode()._Equal("ERR"));
	return request;
}

void calculator::ClientProtocol::processReply(Reply input)
{
	cout << "Message received from server: " << input.getValue() << endl;
}
