#include <boost/asio.hpp>
#include <iostream>
#include <array>
#include "ClientProtocol.h"
#include "ClientProtocolCalc.h"
using namespace std;
using namespace boost;
using namespace calculator;
using asio::ip::tcp;

//#ifndef MAXLINE
//#define MAXLINE 4096 /*max text line length*/
//#define SERV_PORT 3000 /*port*/
//#define LISTENQ 5 /*maximum number of waiting client connections */
//#define EXITMESSAGE "!"
//#endif // !MAXLINE


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
		asio::connect(socket, endpoints);
		for (;;) {
			char buff[MAXLINE];
			system::error_code error;

			string output = app.prepareRequest();
			string input;
			size_t bytes_sent;
			if (output._Equal(EXITMESSAGE)) {
				cout << "EXITING" << endl;
				bytes_sent = asio::write(socket, asio::buffer(output), error);
				socket.close();
				break;
			}
			bytes_sent = asio::write(socket, asio::buffer(output), error);
			size_t len = socket.read_some(asio::buffer(buff), error);
			buff[len] = '\0';
			app.processReply(buff);

			//cout << buff << endl;
		}
	}
	catch (std::exception& e) {
		cout << "[DEBUG] error out of for" << endl;
	}

	return 0;
}
