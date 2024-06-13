#include "ReceiveThread.h"

ReceiveThread::ReceiveThread()
	:mySocket(nullptr), myThread() {}

ReceiveThread::ReceiveThread(std::shared_ptr<tcp::socket> socket)
	: mySocket(socket), myThread() {}

void ReceiveThread::start() {
	myThread = thread([this]() {
		ClientProtocol app;
		char buff[MAXLINE];
		system::error_code error;
		size_t len;

		do {
			len = mySocket->read_some(asio::buffer(buff), error);
			buff[len] = '\0';
			app.processReply(buff);
		} while (len != 0);
	});
}

void ReceiveThread::join()
{
	myThread.join();
}
