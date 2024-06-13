#include "linearBarrier.h"

linearBarrier::linearBarrier(int total)
	: arrived(0), totalThreads(total), waiting(1) {}

void linearBarrier::barrier() {
	unique_lock<mutex> lock(mtx);
	arrived++;
	if (arrived == totalThreads) waiting = false;
	while (waiting) {
		cond.wait(lock);
	}
	arrived--;
	if (arrived == 0) waiting = true;
	cond.notify_all();
}
