#pragma once
#include <cstdlib>
#include <chrono>
//#include "ProdConCondVar/BufferConVar.h"
//#include "ProdConLockCond/BufferLockCond.h"
//#include "ProdConSemMux/BufferSemMux.h"
#include "BufferIncludes.h"
using namespace std;
using namespace chrono;

class Buffer;

class Consumer {
private:
	int scale;
	Buffer* buff;
	thread myThread;

public:
	Consumer();
	Consumer(Buffer* b, int s);
	void start();
	void join();
};

