#include "ServerProtocol.h"

void msg_modification::ServerProtocol::decrypt(string& buff, int offset) {
	char base;
	for (int i = 0; buff[i] != '\0'; ++i) {
		if (buff[i] != ' ') {
			if (buff[i] >= 'a' && buff[i] <= 'z') base = 'a';
			else if (buff[i] >= 'A' && buff[i] <= 'Z') base = 'A';

			int originalAlphabetPos = buff[i] - base;
			int newAlphabetPos = (originalAlphabetPos - offset);
			if (newAlphabetPos < 0) newAlphabetPos += 26;
			buff[i] = base + newAlphabetPos;
		}
	}
}

void msg_modification::ServerProtocol::encrypt(string& buff, int offset) {
	char base;
	for (int i = 0; buff[i] != '\0'; ++i) {
		if (buff[i] != ' ') {
			if (buff[i] >= 'a' && buff[i] <= 'z') base = 'a';
			else if (buff[i] >= 'A' && buff[i] <= 'Z') base = 'A';

			int originalAlphabetPos = buff[i] - base;
			int newAlphabetPos = (originalAlphabetPos + offset) % 26;
			buff[i] = base + newAlphabetPos;
		}
	}
}

void msg_modification::ServerProtocol::to_uppercase(string& buff) {
	for (int i = 0; buff[i] != '\0'; ++i) {
		if (buff[i] >= 'a' && buff[i] <= 'z') {
			buff[i] -= 'a' - 'A';
		}
	}
}

void msg_modification::ServerProtocol::to_lowercase(string& buff) {
	for (int i = 0; buff[i] != '\0'; ++i) {
		if (buff[i] >= 'A' && buff[i] <= 'Z') {
			buff[i] += 'a' - 'A';
		}
	}
}

string msg_modification::ServerProtocol::processRequest(char buff[MAXLINE]) {
	string s = buff;
	string tokens[3];
	size_t pos = 0;

	int i;
	for (i = 0; (pos = s.find(' ')) != std::string::npos; ++i) {
		tokens[i] = s.substr(0, pos);
		s.erase(0, pos + 1);
	}
	tokens[i] = s;

	if (tokens[0].size() != 1 || (!all_of(tokens[0].begin(), tokens[0].end(), isdigit))) {
		return "Incorrect message\n\0";
	}
	int choice = stoi(tokens[0]);
	int offset;
	switch (choice)
	{
	case 1:
		to_lowercase(tokens[1]);
		return tokens[1];
	case 2:
		to_uppercase(tokens[1]);
		return tokens[1];
	case 3:
		if (!all_of(tokens[1].begin(), tokens[1].end(), isdigit)) {
			return "Incorrect message\n\0";
		}
		offset = stoi(tokens[1]);
		encrypt(tokens[2], offset);
		return tokens[2];
	case 4:
		if (!all_of(tokens[1].begin(), tokens[1].end(), isdigit)) {
			return "Incorrect message\n\0";
		}
		offset = stoi(tokens[1]);
		decrypt(tokens[2], offset);
		return tokens[2];
	default:
		break;
	}
}
