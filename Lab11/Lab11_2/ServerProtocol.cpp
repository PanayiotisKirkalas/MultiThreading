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

double calculator::ServerProtocol::doServerComputation(int n)
{
	if (hashTable.find(n) != hashTable.end()) {
		cout << "Already in" << endl;
		return hashTable[n];
	}

	cout << "Not found" << endl;
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

	return pi;
}

double calculator::ServerProtocol::f(double a)
{
	return (4.0 / (1.0 + a * a));
}

double calculator::ServerProtocol::processRequest(int n)
{
	cout << n << endl;
	return doServerComputation(n);
}
