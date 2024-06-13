#include "ClientProtocol.h"

string msg_modification::ClientProtocol::prepareRequest() {
	string input;

	cout << "Enter message to send to server:";
	getline(cin, input);

	/*input[input.size()] = '\n';
	input += '\0';*/

	return input;
}

void msg_modification::ClientProtocol::processReply(string theInput) {
	cout << "Message received from server: " << theInput << endl;
}
