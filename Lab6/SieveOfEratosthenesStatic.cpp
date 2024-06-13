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
	int myFrom, myTo, mySize;
	bool* prime_ptr;
	thread myThread;
	Lock* lock_ptr;

public:
	StaticThread()
		: myFrom(-1), myTo(-1), mySize(-1), prime_ptr(nullptr), myThread(), lock_ptr(nullptr) {}

	StaticThread(int from, int to, int size, bool* prime, Lock* lock = nullptr)
		: myFrom(from), myTo(to), mySize(size), prime_ptr(prime), myThread(), lock_ptr(lock) {}

	void start() {
		myThread = thread([this]() {
			//{
			//	lock_guard<Lock> guard(*lock_ptr);
			//	cout << "Thread: " << std::hex << this_thread::get_id() << endl;
			//	cout << "Vector address: " << prime_ptr << endl;
			//	/*cout << "\t" << myIndex << endl;
			//	cout << "\t" << myLimit << endl;
			//	cout << "\t" << myThreadN << endl;*/
			//}

			
			//lock_guard<Lock> guard(*lock_ptr);
			for (int p = myFrom; p <= myTo; p++) {
				if (prime_ptr[p]) {
					for (int i = p * p; i <= mySize; i += p) {
						// Update all multiples of p
						//prime_ptr->at(i) = false;
						prime_ptr[i] = false;
						//if (prime_ptr->at(i) == true) cout << std::dec << "Error " << i << endl;
					}
				}
			}
		});
	}

	void join() {
		//{
		//	lock_guard<Lock> guard(*lock_ptr);
		//	cout << "Thread: " << std::hex << myThread.get_id() << endl;
		//	/*cout << "\t" << myIndex << endl;
		//	cout << "\t" << myLimit << endl;
		//	cout << "\t" << myThreadN << endl;*/
		//}
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
	//cout << prime.size() * prime[0] << endl;
	bool* prime = new bool[size+1];
	for (int i = 0; i <= size; ++i) {
		prime[i] = true;
	}
	//cout << (size + 1) * sizeof(prime[0]) << endl;

	// Get current time
	auto start = high_resolution_clock::now();

	Lock lock;
	int limit = static_cast<int>(std::sqrt(size)) + 1;
	int block = limit / numThreads;
	int from = 0;
	int to = 0;

	StaticThread* threads = new StaticThread[numThreads];
	//cout << sizeof(threads[0]) * numThreads << endl;

	for (int i = 0; i < numThreads; ++i)
	{
		from = 2 + i * block;
		to = from + block;
		if (i == numThreads - 1) to = limit;
		threads[i] = StaticThread(from, to, size, prime, &lock);
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
		if (prime[i]) {
			++count;
			//if (i%2 == 0)cout << std::dec << i << " ";
		}
	}
	cout << endl;

	cout << "number of primes " << std::dec << count << std::endl;
	cout << "time in ms = " << elapsedTime << std::endl;

	delete[] prime;
	return 0;
}
