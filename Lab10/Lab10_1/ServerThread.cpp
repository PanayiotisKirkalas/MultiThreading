#include "ServerThread.h"

ServerThread::ServerThread()
	: myConnections_ptr(nullptr), myId(-1), lock_ptr(nullptr) {}

ServerThread::ServerThread(std::shared_ptr <vector<tcp::socket>> sockets, int id, std::shared_ptr<recursive_mutex> lock)
	: myConnections_ptr(sockets), myId(id), lock_ptr(lock) {}

void ServerThread::start()
{
	myThread = thread([this]() {
		try {
			char buff[MAXLINE];
			string output;

			ServerProtocol app;
			system::error_code error;
			size_t len;
			len = (*myConnections_ptr)[myId].read_some(asio::buffer(buff), error);
			buff[len] = '\0';
			while (strcmp(buff, EXITMESSAGE)) {
				output = app.processRequest(buff);
				for (int i = 0; i < (*myConnections_ptr).size(); ++i) {
					if (i == myId)
						continue;
					{
						lock_guard<recursive_mutex> guard(*lock_ptr);
						asio::write((*myConnections_ptr)[i], asio::buffer(output), error);
					}
				}
				len = (*myConnections_ptr)[myId].read_some(asio::buffer(buff), error);
				buff[len] = '\0';
			}
			cout << "CONNECTION ENDED" << endl;
			{
				lock_guard<recursive_mutex> guard(*lock_ptr);
				(*myConnections_ptr)[myId].close();
			}
		}
		catch (std::exception& e) {}
	});
	myThread.detach();
}
