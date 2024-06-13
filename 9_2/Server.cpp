#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
//#include "ServerProtocol.h"
//#include "ServerProtocolCalc.h"
#include "ServerThread.h"
using namespace std;
using namespace boost;
//using namespace calculator;
using asio::ip::tcp;

//#ifndef MAXLINE
//#define MAXLINE 4096 /*max text line length*/
//#define SERV_PORT 3000 /*port*/
//#define LISTENQ 5 /*maximum number of waiting client connections */
//#define EXITMESSAGE "!"
//#endif // !MAXLINE

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
		//ServerProtocol app;
		ServerThread *Thread;

		for (;;) {
			socket = std::make_shared<tcp::socket>(ct);
			cout << "Server is listening to port: " << SERV_PORT << endl;
			acceptor.accept(*socket);
			
			cout << "Received request from " << socket->remote_endpoint().address().to_string() << endl;
			/*char buff[MAXLINE];
			string output;

			system::error_code error;
			size_t len = socket.read_some(asio::buffer(buff), error);
			buff[len] = '\0';
			while (strcmp(buff, EXITMESSAGE)) {
				output = app.processRequest(buff);
				asio::write(socket, asio::buffer(output), error);
				len = socket.read_some(asio::buffer(buff), error);
				buff[len] = '\0';
			}
			cout << "CONNECTION ENDED" << endl;
			socket.close();*/
			Thread = new ServerThread(socket);
			Thread->start();
		}
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
}