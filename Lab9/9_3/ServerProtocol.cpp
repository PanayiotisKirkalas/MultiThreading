#include "ServerProtocol.h"

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

void calculator::ServerProtocol::getRequestData(string request, int* n)
{
	string token;
	size_t pos = 0;

	int i;
	/*for (i = 0; (pos = request.find(' ')) != std::string::npos; ++i) {
		token[i] = request.substr(0, pos);
		request.erase(0, pos + 1);
	}
	token[i] = request;
	if (*op == '!')
		return;*/
	try {
		*n = stoi(request);
	}
	catch (std::exception e) {}
}

string calculator::ServerProtocol::doServerComputation(int n)
{
	/*switch (op)
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
	}*/

	if (hashTable.find(n) != hashTable.end()) {
		cout << "Already in" << endl;
		return to_string(hashTable[n]);
	}

	double pi, h, sum, x;
	int i;

	pi = 0.0;
	h = 1.0 / (double)n;
	sum = 0.0;

	for (i = 1; i <= n; i++)
	{
		x = h * ((double)i - 0.5);
		sum += f(x);
	}
	pi = h * sum;

	hashTable[n] = pi;

	return to_string(pi);
}

double calculator::ServerProtocol::f(double a)
{
	return (4.0 / (1.0 + a * a));
}

string calculator::ServerProtocol::processRequest(string buff)
{
	int n;
	getRequestData(buff, &n);
	cout << n << endl;
	string result = doServerComputation(n);
	return result;
}
