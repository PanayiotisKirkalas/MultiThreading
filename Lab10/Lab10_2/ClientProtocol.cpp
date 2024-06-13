#include "ClientProtocol.h"


void ClientProtocol::print_message(const string& buff) {
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

string ClientProtocol::compute(string request)
{
	string tokens = request;
	size_t pos = 0;
	int range;
	int id;
	recursive_mutex lock;

	pos = tokens.find(' ');
	range = stoi(tokens.substr(0, pos));
	id = stoi(tokens.substr(pos + 1, tokens.size()));

	WorkerThread threads[numWorkers];

	cout << "Worker " << id << " calculates " << range << endl;
	int block = range / numWorkers;
	int block2 = block / numWorkers;
	int from = id * block;
	int to = from + block;
	if (id == numWorkers - 1) to = range;
	cout << "Worker " << id << " sums from " << from << " to " << to << endl;

	double step = 1.0 / (double)range;
	double sum = 0.0;

	try {
		for (int i = 0; i < numWorkers; ++i) {
			int from2 = from + block2 * i;
			int to2 = from2 + block2;
			if (i == numWorkers - 1) to2 = to;
			threads[i] = WorkerThread(step, from2, to2, &sum, &lock);
			threads[i].start();
		}
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}

	for (int i = 0; i < numWorkers; ++i) {
		threads[i].join();
	}
	
	return to_string(sum);
}
