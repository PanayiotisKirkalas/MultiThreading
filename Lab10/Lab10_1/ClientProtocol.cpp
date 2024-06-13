#include "ClientProtocol.h"

string ClientProtocol::prepareRequest() {
	string input;

	cout << "Enter message to send to server:";
	getline(cin, input);

	return input;
}

void ClientProtocol::processReply(string theInput) {
	cout << "Received message : " << theInput << endl;
	cout << "Send a reply, CLOSE for exit:";
}
