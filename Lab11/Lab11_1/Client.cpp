#include <iostream>
#include <array>
#include "ClientProtocolCalc.h"
#include "Example1_h.h"
using namespace std;
using namespace calculator;


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
    RPC_STATUS status;
    RPC_WSTR szStringBinding = NULL;

    // Creates a string binding handle.
    // This function is nothing more than a printf.
    // Connection is not done here.
    status = RpcStringBindingCompose(
        NULL,                                        // UUID to bind to.
        (RPC_WSTR)L"ncacn_ip_tcp",// Use TCP/IP protocol.
        (RPC_WSTR)L"localhost",   // TCP/IP network address to use.
        (RPC_WSTR)L"3000",        // TCP/IP port to use.
        NULL,                                    // Protocol dependent network options to use.
        &szStringBinding);                       // String binding output.

    if (status)
        exit(status);

    // Validates the format of the string binding handle and converts
    // it to a binding handle.
    // Connection is not done here either.
    status = RpcBindingFromStringBinding(
        szStringBinding,        // The string binding to validate.
        &hExample1Binding);     // Put the result in the implicit binding
                                // handle defined in the IDL file.

    if (status)
        exit(status);

    try {
        // Calls the RPC function. The hExample1Binding binding handle
        // is used implicitly.
        // Connection is done here.
        ClientProtocol app;
        unsigned char* reply = nullptr;
        string temp = app.prepareRequest();
        while (!temp._Equal(EXITMESSAGE)) {
            unsigned char* request = (unsigned char*)temp.c_str();

            // Ensure request is not nullptr
            if (request == nullptr) {
                throw std::runtime_error("Failed to prepare request");
            }

            ToServer(request, &reply);

            // Ensure reply is not nullptr
            if (reply == nullptr) {
                throw std::runtime_error("Failed to get a valid reply from the server");
            }

            app.processReply((char*)reply);
            temp = app.prepareRequest();
        }

        midl_user_free(reply);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

        // Free the memory allocated by a string.
        status = RpcStringFree(
            &szStringBinding); // String to be freed.

    if (status)
        exit(status);

    // Releases binding handle resources and disconnects from the server.
    status = RpcBindingFree(
        &hExample1Binding); // Frees the implicit binding handle defined in the IDL file.

    if (status)
        exit(status);

	//asio::io_context ct;
	//ClientProtocol app;
	//try {
	//	tcp::resolver resolver(ct);
	//	tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");
	//	tcp::socket socket(ct);
	//	asio::connect(socket, endpoints);
	//	for (;;) {
	//		char buff[MAXLINE];
	//		system::error_code error;

	//		string output = app.prepareRequest();
	//		string input;
	//		size_t bytes_sent;
	//		if (output._Equal(EXITMESSAGE)) {
	//			cout << "EXITING" << endl;
	//			bytes_sent = asio::write(socket, asio::buffer(output), error);
	//			socket.close();
	//			break;
	//		}
	//		bytes_sent = asio::write(socket, asio::buffer(output), error);
	//		size_t len = socket.read_some(asio::buffer(buff), error);
	//		buff[len] = '\0';
	//		app.processReply(buff);

	//		//cout << buff << endl;
	//	}
	//}
	//catch (std::exception& e) {
	//	cout << "[DEBUG] error out of for" << endl;
	//}

	return 0;
}

// Memory allocation function for RPC.
// The runtime uses these two functions for allocating/deallocating
// enough memory to pass the string to the server.
void* __RPC_USER midl_user_allocate(size_t size)
{
    return malloc(size);
}

// Memory deallocation function for RPC.
void __RPC_USER midl_user_free(void* p)
{
    free(p);
}