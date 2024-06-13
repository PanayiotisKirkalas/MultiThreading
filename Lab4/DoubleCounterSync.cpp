#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
using std::thread;
using std::cout;
using std::endl;
using std::recursive_mutex;
using std::lock_guard;
using std::srand;
using std::rand;

class SharedCounter {
	int c1, c2;
	recursive_mutex mutex1, mutex2;

public:
	SharedCounter()
		: c1(0), c2(0), mutex1(), mutex2() {}

	int getC1() {
		//C++ doesn't support "synchronized".
		//Instead it implements RAII (Resource Acquisition Is Initialization)
		//for more details: https://en.cppreference.com/w/cpp/language/raii
		lock_guard<recursive_mutex> lock(mutex1);
		return c1;
	}

	int getC2() {
		//C++ doesn't support "synchronized".
		//Instead it implements RAII (Resource Acquisition Is Initialization)
		//for more details: https://en.cppreference.com/w/cpp/language/raii
		lock_guard<recursive_mutex> lock(mutex2);
		return c2;
	}

	void incC1() {
		//C++ doesn't support "synchronized".
		//Instead it implements RAII (Resource Acquisition Is Initialization)
		//for more details: https://en.cppreference.com/w/cpp/language/raii
		lock_guard<recursive_mutex> lock(mutex1);
		++c1;
	}

	void incC2() {
		//C++ doesn't support "synchronized".
		//Instead it implements RAII (Resource Acquisition Is Initialization)
		//for more details: https://en.cppreference.com/w/cpp/language/raii
		lock_guard<recursive_mutex> lock(mutex2);
		++c2;
	}
};

class CounterThread {
	thread myThread;
	SharedCounter* counter_ptr;

public:
	CounterThread()
		: myThread(), counter_ptr(nullptr) {}

	CounterThread(SharedCounter* counter)
		: myThread(), counter_ptr(counter) {};

	void start() {
		myThread = thread([this]() {
			srand(time(0));
			for (int i = 0; i < 10000; i++)
				((rand() % 2) == 0) ? counter_ptr->incC1() : counter_ptr->incC2();
			});
	}

	void join() {
		myThread.join();
	}
};

int main() {
	constexpr int numThreads = 4;
	CounterThread threads[numThreads];
	SharedCounter counter;

	for (int i = 0; i < numThreads; i++) {
		threads[i] = CounterThread(&counter);
		threads[i].start();
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	cout << "c1: " << counter.getC1() << endl << "c2: " << counter.getC2() << endl;

	return 0;
}
