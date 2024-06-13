#include <ctime>
#include <iostream>
#include <string>
//#include <boost/asio.hpp>
//#include "ServerProtocol.h"
#include "ServerProtocolCalc.h"
#include "Source_h.h"
using namespace std;
//using namespace boost;
using namespace calculator;
//using asio::ip::tcp;

//#ifndef MAXLINE
//#define MAXLINE 4096 /*max text line length*/
//#define SERV_PORT 3000 /*port*/
//#define LISTENQ 5 /*maximum number of waiting client connections */
//#define EXITMESSAGE "!"
//#endif // !MAXLINE

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

void* __RPC_USER midl_user_allocate(size_t size)
{
	return malloc(size);
}

// Memory deallocation function for RPC.
void __RPC_USER midl_user_free(void* p)
{
	free(p);
}

// Server function.
void ToServer(const unsigned char* szRequest, unsigned char** szReply)
{
	ServerProtocol app;

	string answer = app.processRequest((char*)szRequest);

	*szReply = (unsigned char*)midl_user_allocate(answer.size() + 1);
	strcpy(*(char**)szReply, answer.c_str());
}


// Naive security callback.
RPC_STATUS CALLBACK SecurityCallback(RPC_IF_HANDLE /*hInterface*/, void* /*pBindingHandle*/)
{
	return RPC_S_OK; // Always allow anyone.
}

int main() {
	RPC_STATUS status;

	status = RpcServerUseProtseqEp((RPC_WSTR)L"ncacn_ip_tcp", RPC_C_PROTSEQ_MAX_REQS_DEFAULT, (RPC_WSTR)L"3000", NULL);
	if (status) {
		exit(status);
	}

	// Registers the Example1 interface.
	status = RpcServerRegisterIf2(
		Calculator_v1_0_s_ifspec,              // Interface to register.
		NULL,                                // Use the MIDL generated entry-point vector.
		NULL,                                // Use the MIDL generated entry-point vector.
		RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH, // Forces use of security callback.
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,      // Use default number of concurrent calls.
		(unsigned)-1,                        // Infinite max size of incoming data blocks.
		SecurityCallback);                   // Naive security callback.

	if (status) {
		std::cout << "[DEBUG 2]" << std::endl;
		exit(status);
	}

	status = RpcServerListen(
		1,                                   // Recommended minimum number of threads.
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,      // Recommended maximum number of threads.
		FALSE);                              // Start listening now.

	if (status) {
		std::cout << "[DEBUG 3]" << std::endl;
		exit(status);
	}

	//try {
	//	//asio::io_context ct;
	//	//tcp::acceptor acceptor(ct, tcp::endpoint(tcp::v4(), 3000));
	//	//tcp::socket socket(ct);
	//	ServerProtocol app;

	//	for (;;) {
	//		//acceptor.accept(socket);
	//		char buff[MAXLINE];
	//		string output;

	//		//system::error_code error;
	//		//size_t len = socket.read_some(asio::buffer(buff), error);
	//		//buff[len] = '\0';
	//		while (strcmp(buff, EXITMESSAGE)) {
	//			//output = app.processRequest(buff);
	//			//asio::write(socket, asio::buffer(output), error);
	//			//len = socket.read_some(asio::buffer(buff), error);
	//			//buff[len] = '\0';
	//		}
	//		cout << "CONNECTION ENDED" << endl;
	//		//socket.close();
	//	}
	//}
	//catch (std::exception& e) {
	//	cout << e.what() << endl;
	//}
}