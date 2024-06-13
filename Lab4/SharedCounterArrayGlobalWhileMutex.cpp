#include <iostream>
#include <thread>
#include <mutex>
using std::thread;
using std::cout;
using std::endl;
using std::recursive_mutex;

void check_array(int end, int* array) {
	int errors = 0;
	std::cout << "Checking..." << std::endl;

	for (int i = 0; i < end; i++) {
		if (array[i] != 1) {
			errors++;
			std::cout << i << ": " << array[i] << " should be 1" << std::endl;
		}
	}
	std::cout << errors << " errors." << std::endl;
}

class CounterThread {
	int myEnd;
	int* array_ptr, * counter_ptr;
	thread myThread;
	recursive_mutex* myMutex;

public:
	CounterThread()
		:myThread(), array_ptr(nullptr), counter_ptr(nullptr), myEnd(-1), myMutex() {}

	CounterThread(int end, int* array, int* counter, recursive_mutex* mutex)
		:myThread(), array_ptr(array), counter_ptr(counter), myEnd(end), myMutex(mutex) {}

	void start() {
		myThread = thread([this]() {
			while (true) {
				//C++ doesn't support "try-finally".
				myMutex->lock();
				try {
					if ((*counter_ptr) >= myEnd) {
						myMutex->unlock();
						break;
					}
					array_ptr[*counter_ptr]++;
					(*counter_ptr)++;
					myMutex->unlock();
				} catch (...) {}
			}
		});
	}

	void join() {
		myThread.join();
	}
};

int main() {
	constexpr int end = 10000;
	int counter = 0;
	int* array = new int[end];
	constexpr int numThreads = 4;
	CounterThread threads[numThreads];
	recursive_mutex lock;

	for (int i = 0; i < end; ++i) {
		array[i] = 0;
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i] = CounterThread(end, array, &counter, &lock);
		threads[i].start();
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	check_array(end, array);

	return 0;
}
