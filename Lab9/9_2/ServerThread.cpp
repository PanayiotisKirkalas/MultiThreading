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

			string i_archive_data(buff, len);
			istringstream i_archive_stream(i_archive_data);
			archive::binary_iarchive i_archive(i_archive_stream);


			Request request;
			i_archive >> request;
			cout << "Request: " << request.getOpcode() << " " << request.getFirst() << " " << request.getSecond() << endl;
			Reply rep;

			while (!request.getOpcode()._Equal(EXITMESSAGE)) {
				ostringstream o_archive_stream;
				rep = app.processRequest(request);
				archive::binary_oarchive o_archive(o_archive_stream);
				o_archive << rep;
				output = o_archive_stream.str();
				//cout << "Reply: " << output << endl;
				
				asio::write(*mySocket, asio::buffer(output), error);

				len = mySocket->read_some(asio::buffer(buff), error);
				buff[len] = '\0';
				i_archive_data = std::string(buff, len);
				i_archive_stream = std::istringstream(i_archive_data);
				archive::binary_iarchive i_archive(i_archive_stream);

				request;
				i_archive >> request;
				cout << "Request: " << request.getOpcode() << " " << request.getFirst() << " " << request.getSecond() << endl;
			}
			cout << "CONNECTION ENDED" << endl;
			mySocket->close();
		}
		catch (std::exception& e) {}
	});
	myThread.detach();
}
