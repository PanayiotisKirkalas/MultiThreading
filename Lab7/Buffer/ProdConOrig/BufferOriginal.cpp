#include "BufferOriginal.h"

Buffer::Buffer(int s) 
    : size(s), front(0), back(s - 1), counter(0) {
    contents = new int[size];
    for (int i = 0; i < size; i++)
        contents[i] = 0;
}

void Buffer::put(int data) {
    while (counter == size) {}
    back = (back + 1) % size;
    contents[back] = data;
    counter++;
    std::cout << "Item " << data << " added in loc " << back << ". Count = " << counter << std::endl;
    if (counter == size)
        std::cout << "The buffer is full" << std::endl;
}

int Buffer::get() {
    while (counter == 0) {}
    int data = contents[front];
    std::cout << "Item " << data << " removed from loc " << front << ". Count = " << (counter - 1) << std::endl;
    front = (front + 1) % size;
    counter--;
    if (counter == 0)
        std::cout << "The buffer is empty" << std::endl;
    return data;
}