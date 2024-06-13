#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include "ClientProtocol.h"
#include "ReceiveThread.h"
#include "SendThread.h"
using namespace std;
using namespace boost;
using asio::ip::tcp;

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
	try {
		tcp::resolver resolver(ct);
		tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");
		std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(tcp::socket(ct));
		asio::connect(*socket, endpoints);
		cout << "Connected to " << socket->remote_endpoint().address().to_string() << endl;

		SendThread send(socket);
		send.start();
		ReceiveThread receive(socket);
		receive.start();

		send.join();
		receive.join();
	}
	catch (std::exception& e) {
		cout << "[DEBUG] error" << endl;
	}

	return 0;
}
