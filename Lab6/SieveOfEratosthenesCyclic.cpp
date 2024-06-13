#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <chrono>
#include <string>
using namespace std;
using namespace chrono;
#define Lock recursive_mutex

class StaticThread
{
	int myIndex, myLimit, mySize, myThreadN;
	bool* prime_ptr;
	thread myThread;
	Lock* lock_ptr;

public:
	StaticThread()
		: myIndex(-1), myLimit(-1), mySize(-1), myThreadN(-1), prime_ptr(nullptr), myThread(), lock_ptr(nullptr) {}

	StaticThread(int index, int limit, int size, int threadN, bool* prime, Lock* lock = nullptr)
		: myIndex(index + 2), myLimit(limit), mySize(size), myThreadN(threadN), prime_ptr(prime), myThread(), lock_ptr(lock) {}

	void start() {
		myThread = thread([this]() {
			//{
			//	lock_guard<Lock> guard(*lock_ptr);
			//	cout << "Thread: " << std::hex << this_thread::get_id() << endl;
			//	/*cout << "\t" << myIndex << endl;
			//	cout << "\t" << myLimit << endl;
			//	cout << "\t" << myThreadN << endl;*/
			//}

			// Update all multiples of p
			int i = 0;
			//lock_guard<Lock> guard(*lock_ptr);
			for (int p = myIndex; p <= myLimit; p += myThreadN) {
				if (prime_ptr[p]) {
					for (i = p * p; i <= mySize; i += p) {
						/*if (myIndex == 4) {
							lock_guard<Lock> guard(*lock_ptr);
							cout << i << endl;
						}*/
						prime_ptr[i] = false;
					}
				}
			}
			});
	}

	void join() {
		myThread.join();
	}
};

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: <exe name> <size>" << std::endl;
		return 1;
	}

	int size = stoi(argv[1]);
	int numThreads = thread::hardware_concurrency();

	if (size <= 0) {
		cout << "size should be a positive integer" << std::endl;
		return 1;
	}

	//vector<bool> prime(size + 1, true);
	bool* prime = new bool[size + 1];
	for (int i = 0; i <= size; ++i) {
		prime[i] = true;
	}

	// Get current time
	auto start = high_resolution_clock::now();

	Lock lock;
	int limit = static_cast<int>(std::sqrt(size)) + 1;

	StaticThread* threads = new StaticThread[numThreads];

	for (int i = 0; i < numThreads; ++i)
	{
		threads[i] = StaticThread(i, limit, size, numThreads, prime, &lock);
		threads[i].start();
	}

	//cin.get();
	// wait for threads to terminate            
	for (int i = 0; i < numThreads; ++i) {
		try {
			threads[i].join();
		}
		catch (exception e) {}
	}

	//int limit = static_cast<int>(std::sqrt(size)) + 1;
	//for (int p = 2; p <= limit; ++p) {
	//    if (prime[p]) {
	//        // Update all multiples of p
	//        for (int i = p * p; i <= size; i += p)
	//            prime[i] = false;
	//    }
	//}

	// Get current time and calculate elapsed time
	double elapsedTime = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();

	int count = 0;
	for (int i = 2; i <= size; ++i) {
		if (prime[i])
			++count;
	}

	cout << "number of primes " << std::dec << count << std::endl;
	cout << "time in ms = " << elapsedTime << std::endl;

	return 0;
}
