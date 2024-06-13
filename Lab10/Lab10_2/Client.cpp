#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include "ClientProtocol.h"
#include "WorkerThread.h"
using namespace std;
using namespace boost;
using asio::ip::tcp;

#ifndef numWorkers
#define numWorkers 4
#endif // !numWorkers


void print_message(const string& buff) {
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

int main() {
	asio::io_context ct;
	ClientProtocol app;
	try {
		tcp::resolver resolver(ct);
		tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");
		tcp::socket socket(ct);
		WorkerThread threads[numWorkers];
		asio::connect(socket, endpoints);
		char buff[MAXLINE];
		system::error_code error;

		ClientProtocol app;
		size_t len = socket.read_some(asio::buffer(buff), error);
		buff[len] = '\0';
		string output = app.compute(buff);
		size_t bytes_sent;
		bytes_sent = asio::write(socket, asio::buffer(output), error);

		socket.close();
	}
	catch (std::exception& e) {
		cout << "Client.cpp\n" << e.what() << endl;
	}

	return 0;
}
