#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class cyclicBarrier {
private:
    int arrived;
    int totalThreads;
    bool waiting, leaving;
    mutex mtx;
    condition_variable cWait, cLeave;

public:
    cyclicBarrier(int total);

    void barrier();
};

