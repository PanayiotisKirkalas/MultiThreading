#include <iostream>
#include <array>
#include "ClientProtocol.h"
#include "Source_h.h"
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
        double reply;
        int temp = app.prepareRequest();
        while (temp != EXITMESSAGE) {
            int request = temp;

            ToServer(request, &reply);

            app.processReply(reply);
            temp = app.prepareRequest();
        }
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