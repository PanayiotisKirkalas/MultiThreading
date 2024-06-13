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
		*a = stof(tokens[1]);
		*b = stof(tokens[2]);
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

Reply calculator::ServerProtocol::processRequest(Request req)
{
	Reply res;
	string op = req.getOpcode();
	float a = req.getFirst(), b = req.getSecond();
	/*getRequestData(buff, &op, &a, &b);
	string result = doServerComputation(op, a, b);
	return result;*/

	if (op._Equal("ADD")) {
		res.setOpcode("OK");
		res.setValue(a + b);
	}
	else if (op._Equal("SUB")) {
		res.setOpcode("OK");
		res.setValue(a - b);

	}
	else if (op._Equal("MUL")) {
		res.setOpcode("OK");
		res.setValue(a * b);

	}
	else if (op._Equal("DIV")) {
		if (b != 0) {
			res.setOpcode("OK");
			res.setValue(a + b);
		}
		else {
			res.setOpcode("ERR");
			res.setValue(-9999);
		}
	}
	else {
		res.setOpcode("ERR");
		res.setValue(-9999);
	}
	return res;
}
