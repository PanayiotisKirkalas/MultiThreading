#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "ServerThread.h"
using namespace std;
using namespace boost;
using asio::ip::tcp;

#define numWorkers 4

//For debugging purposes
void print_message(const string& buff) {
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

int main() {
	try {
		asio::io_context ct;
		tcp::acceptor acceptor(ct, tcp::endpoint(tcp::v4(), 3000));
		std::shared_ptr<tcp::socket> socket;
		ServerThread Thread[numWorkers];
		Sum sum(1000000);

		for (int id = 0; id < numWorkers; ++id) {
			socket = make_shared<tcp::socket>(ct);
			cout << "Server is listening to port: " << SERV_PORT << endl;
			acceptor.accept(*socket);
			
			cout << "Received request from " << socket->remote_endpoint().address().to_string() << endl;
			Thread[id] = ServerThread(socket, id, &sum);
			Thread[id].start();
		}

		for (int i = 0; i < numWorkers; ++i) {
			Thread[i].join();
		}

		cout << "Result: " << sum.getResult() << endl;
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
}