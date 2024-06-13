#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
//#include "ProdConCondVar/BufferConVar.h"
//#include "ProdConLockCond/BufferLockCond.h"
//#include "ProdConSemMux/BufferSemMux.h"
#include "BufferIncludes.h"
#include "Consumer.h"
#include "Producer.h"
using namespace std;

int main() {
	srand(time(0));

	int bufferSize = 5;
	int noIterations = 20;
	int producerDelay = 1;
	int consumerDelay = 100;
	int noProds = 2;
	int noCons = 2;

	Buffer buff(bufferSize);

	Producer* producers = new Producer[noProds];
	Consumer* consumers = new Consumer[noCons];

	// Producer threads
	for (int i = 0; i < noProds; i++) {
		producers[i] = Producer(&buff, noIterations, producerDelay);
		producers[i].start();
	}

	// Consumer threads
	for (int j = 0; j < noCons; j++) {
		consumers[j] = Consumer(&buff, consumerDelay);
		consumers[j].start();
	}

	// Join threads
	for (int i = 0; i < noProds; i++) {
		producers[i].join();
	}
	for (int j = 0; j < noCons; j++) {
		consumers[j].join();
	}

	/*delete[] producers;
	delete[] consumers;*/

	return 0;
}
