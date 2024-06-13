#pragma once
#include <iostream>
using namespace std;

class Buffer {
private:
    int* contents;
    const int size;
    int front, back, counter;

public:
    Buffer(int s);

    void put(int data);

    int get();
};

