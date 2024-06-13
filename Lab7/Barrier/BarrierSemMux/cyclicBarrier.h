#pragma once
#include <iostream>
#include <semaphore>
#include <thread>
using namespace std;

#define c_sem counting_semaphore
#define b_sem binary_semaphore

class cyclicBarrier{
private:
    int arrived;
    int totalThreads;
    c_sem<> mutex, waiting, leaving;

public:
    cyclicBarrier(int total);
    void barrier();
};
