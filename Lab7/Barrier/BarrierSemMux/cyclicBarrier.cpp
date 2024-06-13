#include "cyclicBarrier.h"

cyclicBarrier::cyclicBarrier(int total)
	: arrived(0), totalThreads(total), mutex(1), waiting(0), leaving(1) {}

void cyclicBarrier::barrier() {
    try {
        mutex.acquire();
        arrived++;
        if (arrived == totalThreads) {
            waiting.release();
            leaving.acquire();
        }
    }
    catch (exception e) {};
    mutex.release();

    try {
        std::cout << "waiting " << this_thread::get_id() << std::endl;
        waiting.acquire();
    }
    catch (exception e) {};
    waiting.release();

    try {
        mutex.acquire();
        arrived--;
        if (arrived == 0) {
            waiting.acquire();
            leaving.release();
        }
    }
    catch (exception e) {};
    mutex.release();

    try {
        std::cout << "leaving " << std::this_thread::get_id() << std::endl;
        leaving.acquire();
    }
    catch (exception e) {};
    leaving.release();
}
