#include "BufferConVar.h"

Buffer::Buffer(int s) : size(s), front(0), back(-1), counter(0), bufferEmpty(true), bufferFull(false) {
    contents = new int[size];
    for (int i = 0; i < size; i++)
        contents[i] = 0;
}

void Buffer::put(int data) {
    unique_lock<mutex> lock(mtx);
    notFull.wait(lock, [this] { return !bufferFull; });

    back = (back + 1) % size;
    contents[back] = data;
    counter++;
    cout << "Item " << data << " added in loc " << back << ". Count = " << counter << endl;
    bufferEmpty = false;
    if (counter == size) {
        bufferFull = true;
        cout << "The buffer is full" << endl;
    }
    if (counter == 1) notEmpty.notify_all();
}

int Buffer::get() {
    unique_lock<mutex> lock(mtx);
    notEmpty.wait(lock, [this] { return !bufferEmpty; });

    int data = contents[back];
    counter--;
    cout << "Item " << data << " removed from loc " << front << ". Count = " << counter << endl;
    //front = (front + 1) % size;
    bufferFull = false;
    if (counter == 0) {
        bufferEmpty = true;
        cout << "The buffer is empty" << endl;
    }
    if (counter == size - 1) notFull.notify_all();
    return data;
}