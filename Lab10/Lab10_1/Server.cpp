#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <boost/asio.hpp>
#include "ServerThread.h"
using namespace std;
using namespace boost;
using asio::ip::tcp;

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
		std::shared_ptr<std::recursive_mutex> lock = std::make_shared<std::recursive_mutex>();
		asio::io_context ct;
		tcp::acceptor acceptor(ct, tcp::endpoint(tcp::v4(), 3000));
		ServerThread *Thread;
		std::shared_ptr <vector<tcp::socket>> connections = std::make_shared<std::vector<tcp::socket>>();

		for (int id = 0;;++id) {
			//socket = make_shared<tcp::socket>(ct);
			connections->push_back(tcp::socket(ct));
			cout << "Server is listening to port: " << SERV_PORT << endl;
			acceptor.accept((*connections)[id]);

			cout << "Received request from " << (*connections)[id].remote_endpoint().address().to_string() << endl;

			Thread = new ServerThread(connections, id, lock);
			Thread->start();
		}
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
}