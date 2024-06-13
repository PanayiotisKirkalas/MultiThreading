#pragma once
#include <cstdlib>
#include <chrono>
//#include "ProdConCondVar/BufferConVar.h"
//#include "ProdConLockCond/BufferLockCond.h"
//#include "ProdConSemMux/BufferSemMux.h"
#include "BufferIncludes.h"
using namespace std;
using namespace chrono;

class Producer {
private:
	int reps;
	int scale;
	Buffer* buff;
	thread myThread;

public:
	Producer();
	Producer(Buffer* b, int r, int s);
	void start();
	void join();
};
