#include "cyclicBarrier.h"

cyclicBarrier::cyclicBarrier(int total) 
	: arrived(0), totalThreads(total), waiting(false), leaving(true) {}

void cyclicBarrier::barrier() {
	unique_lock<mutex> lock(mtx);
	arrived++;
	if (arrived == totalThreads) {
		waiting = true;
		leaving = false;
	}
	cWait.wait(lock, [this] { return waiting; });
	cWait.notify_all();
	lock.unlock();

	lock.lock();
	arrived--;
	if (arrived == 0) {
		waiting = false;
		leaving = true;
	}
	cLeave.wait(lock, [this] { return leaving; });
	cLeave.notify_all();
}
