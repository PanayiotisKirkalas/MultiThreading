#include "Producer.h"

Producer::Producer()
    : reps(0), scale(-1), buff(nullptr), myThread() {}

Producer::Producer(Buffer* b, int r, int s)
	: buff(b), reps(r), scale(s), myThread() {}

void Producer::start()
{
	myThread = thread([this]() {
        for (int i = 0; i < reps; i++) {
            buff->put(i);
            this_thread::sleep_for(milliseconds(rand() % scale));
        }
	});
}

void Producer::join()
{
    myThread.join();
}
