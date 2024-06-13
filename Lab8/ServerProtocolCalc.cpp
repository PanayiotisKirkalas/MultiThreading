#include "ServerProtocolCalc.h"

void calculator::ServerProtocol::print_message(const string& buff) {
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

void calculator::ServerProtocol::getRequestData(string request, char* op, float* a, float* b)
{
	string tokens[3];
	size_t pos = 0;

	int i;
	for (i = 0; (pos = request.find(' ')) != std::string::npos; ++i) {
		tokens[i] = request.substr(0, pos);
		request.erase(0, pos + 1);
	}
	tokens[i] = request;
	*op = tokens[0][0];
	if (*op == '!')
		return;
	try {
		*a = stoi(tokens[1]);
		*b = stoi(tokens[2]);
	}
	catch (std::exception e) {
		*op = '!';
	}
}

string calculator::ServerProtocol::doServerComputation(char op, float a, float b)
{
	switch (op)
	{
	case '+':
		return "R " + to_string(a + b);
	case '-':
		return "R " + to_string(a - b);
	case '*':
		return "R " + to_string(a * b);
	case '/':
		return "R " + to_string(a / b);
	case '!':
		return "!";
	default:
		break;
	}
}

string calculator::ServerProtocol::processRequest(string buff)
{
	char op;
	float a, b;
	getRequestData(buff, &op, &a, &b);
	string result = doServerComputation(op, a, b);
	return result;
}
