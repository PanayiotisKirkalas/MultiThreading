#include "BufferSemMux.h"

Buffer::Buffer(int s) : size(s), front(0), back(s - 1), counter(0), mutex(1), bufferFull(0), bufferEmpty(s) {
    contents = new int[s];
}

void Buffer::put(int data) {
    try {
        bufferEmpty.acquire();
    }
    catch (exception e) {}
    /*try {
        mutex.acquire();
    }
    catch (exception e) {}*/
    back = (back + 1) % size;
    contents[back] = data;
    counter++;
    cout << "Prod " << hex << this_thread::get_id() << dec << " No " << data << " Loc " << back << " Count = " << counter << endl;
    if (counter == size) cout << "The buffer is full" << endl;
    //mutex.release();
    bufferFull.release();
}

int Buffer::get() {
    int data = 0;
    try {
        bufferFull.acquire();
    }
    catch (exception e) {}
    /*try {
        mutex.acquire();
    }
    catch (exception e) {}*/
    data = contents[front];
    cout << "  Cons " << hex << this_thread::get_id() << dec << " No " << data << " Loc " << front << " Count = " << (counter - 1) << endl;
    front = (front + 1) % size;
    counter--;
    if (counter == 0) cout << "The buffer is empty" << endl;
    //mutex.release();
    bufferEmpty.release();
    return data;
}

Buffer::~Buffer() {
    delete[] contents;
}