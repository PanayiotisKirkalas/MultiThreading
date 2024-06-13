#include <ctime>
#include <iostream>
#include <string>
#include "ServerProtocol.h"
#include "Source_h.h"
using namespace std;
using namespace calculator;
ServerProtocol app;

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
void ToServer(int szRequest, double* szReply)
{
	double answer = app.processRequest(szRequest);
	*szReply = answer;
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
		exit(status);
	}

	status = RpcServerListen(
		1,                                   // Recommended minimum number of threads.
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,      // Recommended maximum number of threads.
		FALSE);                              // Start listening now.

	if (status) {
		exit(status);
	}
}