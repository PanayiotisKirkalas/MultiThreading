#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class linearBarrier {
private:
    int arrived;
    int totalThreads;
    bool waiting;
    mutex mtx;
    condition_variable cond;

public:
    linearBarrier(int total);

    void barrier();
};

