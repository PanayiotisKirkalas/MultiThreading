#include <iostream>
#include <thread>
using std::thread;
using std::cout;
using std::endl;

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
	int *array_ptr;
	thread myThread;

public:
	CounterThread()
		: myThread(), array_ptr(nullptr), myEnd(-1) {}

	CounterThread(int end, int* array)
		: myThread(), myEnd(end), array_ptr(array) {};

	void start() {
		myThread = thread([this]() {
			for (int i = 0; i < myEnd; i++) {
				for (int j = 0; j < i; j++)
					array_ptr[i]++;
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

	for (int i = 0; i < end; ++i) {
		array[i] = 0;
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i] = CounterThread(end, array);
		threads[i].start();
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	check_array(end, array, numThreads);

	return 0;
}
