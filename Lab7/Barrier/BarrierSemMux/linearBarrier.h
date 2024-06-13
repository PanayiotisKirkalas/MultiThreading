#pragma once
#include <iostream>
#include <semaphore>
#include <thread>
using namespace std;

#define c_sem counting_semaphore
#define b_sem binary_semaphore

class linearBarrier {
private:
    int arrived;
    int totalThreads;
    c_sem<> waiting;
    c_sem<> leaving;

public:
    linearBarrier(int total);
    void barrier();
};