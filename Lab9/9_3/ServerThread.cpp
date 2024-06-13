#include "ServerThread.h"

ServerThread::ServerThread()
	: mySocket(nullptr) {}

ServerThread::ServerThread(std::shared_ptr<tcp::socket> socket)
	: mySocket(socket) {}

void ServerThread::start()
{
	myThread = thread([this]() {
		try {
			char buff[MAXLINE];
			string output;

			ServerProtocol app;
			system::error_code error;
			size_t len = mySocket->read_some(asio::buffer(buff), error);
			buff[len] = '\0';
			while (strcmp(buff, EXITMESSAGE)) {
				output = app.processRequest(buff);
				asio::write(*mySocket, asio::buffer(output), error);
				len = mySocket->read_some(asio::buffer(buff), error);
				buff[len] = '\0';
			}
			cout << "CONNECTION ENDED" << endl;
			mySocket->close();
		}
		catch (std::exception& e) {}
	});
	myThread.detach();
}
