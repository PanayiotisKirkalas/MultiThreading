#pragma once
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

class Buffer {
private:
    int* contents;
    bool bufferEmpty, bufferFull;
    int size;
    int front, back, counter;
    mutex mtx;
    condition_variable notEmpty, notFull;

public:
    Buffer(int s);
    void put(int data);
    int get();
};
