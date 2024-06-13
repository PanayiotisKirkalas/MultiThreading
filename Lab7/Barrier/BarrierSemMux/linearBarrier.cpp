#include "linearBarrier.h"

linearBarrier::linearBarrier(int total)
	: arrived(0), totalThreads(total), waiting(1), leaving(0) {}

void linearBarrier::barrier() {
    try {
        waiting.acquire();
        arrived++;
        std::cout << "waiting " << this_thread::get_id() << std::endl;
        if (arrived == totalThreads) {
            leaving.release();
        }
    }
    catch (exception e) {};
    waiting.release();

    try {
        std::cout << "leaving " << std::this_thread::get_id() << std::endl;
        leaving.acquire();
    }
    catch (exception e) {};
    leaving.release();
}