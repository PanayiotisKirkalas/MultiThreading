#include <iostream>
#include <thread>
#include <mutex>
using std::thread;
using std::cout;
using std::endl;
using std::recursive_mutex;

void check_array(int end, int* array, int numThreads) {
	int errors = 0;
	cout << "Checking..." << endl;

	for (int i = 0; i < end; i++) {
		if (array[i] != numThreads * i) {
			errors++;
			cout << i << ": " << array[i] << " should be " << numThreads * i << endl;
		}
	}
	cout << errors << " errors." << endl;
}

class CounterThread {
	int myEnd;
	int* array_ptr;
	thread myThread;
	recursive_mutex* myMutex;

public:
	CounterThread()
		: myThread(), array_ptr(nullptr), myEnd(-1), myMutex() {}

	CounterThread(int end, int* array, recursive_mutex* mutex)
		: myThread(), myEnd(end), array_ptr(array), myMutex(mutex) {};

	void start() {
		myThread = thread([this]() {
			for (int i = 0; i < myEnd; i++) {
				//C++ doesn't support "try-finally".
				myMutex->lock();
				try {
					for (int j = 0; j < i; j++)
						array_ptr[i]++;
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
	constexpr int end = 1000;
	int array[end];
	constexpr int numThreads = 4;
	CounterThread threads[numThreads];
	recursive_mutex lock;

	for (int i = 0; i < end; ++i) {
		array[i] = 0;
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i] = CounterThread(end, array, &lock);
		threads[i].start();
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	check_array(end, array, numThreads);

	return 0;
}
