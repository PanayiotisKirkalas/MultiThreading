#pragma once
#include <random>
#include <thread>
#include "barrierIncludes.h"
using namespace std;

class testThread {
private:
	int threadID;
	Barrier* myBarrier;
	thread myThread;

public:
	testThread();
	testThread(int tid, Barrier* bar);
	void start();
	void join();
};