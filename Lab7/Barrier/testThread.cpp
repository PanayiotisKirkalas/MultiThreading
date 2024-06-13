#include "testThread.h"

testThread::testThread()
	:threadID(-1), myBarrier(nullptr), myThread() {}

testThread::testThread(int tid, Barrier* bar) : threadID(tid), myBarrier(bar), myThread() {}

void testThread::start() {
	myThread = thread([this]() {
		for (;;) {
			cout << "Thread " << threadID << " started" << endl;
			myBarrier->barrier();
			this_thread::sleep_for(chrono::milliseconds((int)(rand() % 1000)));
			cout << "Thread " << threadID << " reached barrier" << endl;
			myBarrier->barrier();
			cout << "Thread " << threadID << " passed barrier" << endl;
			myBarrier->barrier();
		}
	});
}

void testThread::join() {
	myThread.join();
}
