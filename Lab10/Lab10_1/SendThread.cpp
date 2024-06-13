#include "SendThread.h"

SendThread::SendThread()
	:mySocket(nullptr), myThread() {}

SendThread::SendThread(std::shared_ptr<tcp::socket> socket)
	: mySocket(socket), myThread() {}

void SendThread::start()
{
	myThread = thread([this]() {
		size_t bytes_sent;
		ClientProtocol app;
		string output = app.prepareRequest();
		system::error_code error;

		while (!output._Equal(EXITMESSAGE)) {
			bytes_sent = asio::write(*mySocket, asio::buffer(output), error);
			output = app.prepareRequest();
		}
		cout << "EXITING" << endl;
		bytes_sent = asio::write(*mySocket, asio::buffer(output), error);
		mySocket->close();
	});
}

void SendThread::join()
{
	myThread.join();
}
