#include "ServerThread.h"

ServerThread::ServerThread()
	: mySocket(nullptr), sum_ptr(nullptr), myID(-1) {}

ServerThread::ServerThread(std::shared_ptr<tcp::socket> socket, int id, Sum* sum)
	: mySocket(socket), myID(id), sum_ptr(sum) {}

void ServerThread::start()
{
	myThread = thread([this]() {
		try {
			char buff[MAXLINE];
			string output;

			ServerProtocol app(sum_ptr->getInit(), myID);
			system::error_code error;
			size_t len;
			output = app.prepareRequest();
			asio::write(*mySocket, asio::buffer(output), error);
			len = mySocket->read_some(asio::buffer(buff), error);
			buff[len] = '\0';
			sum_ptr->addTo(app.processReply(buff));
			cout << "CONNECTION ENDED" << endl;
			mySocket->close();
		}
		catch (std::exception& e) {}
	});
}

void ServerThread::join()
{
	myThread.join();
}
