#pragma once
#include <iostream>
#include <semaphore>
using namespace std;

#define c_sem counting_semaphore
#define b_sem binary_semaphore

class Buffer {
private:
    int* contents;
    int size;
    int front, back;
    int counter;
    b_sem mutex;
    c_sem<> bufferFull;
    c_sem<> bufferEmpty;

public:
    Buffer(int s);
    ~Buffer();
    void put(int data);
    int get();
};

