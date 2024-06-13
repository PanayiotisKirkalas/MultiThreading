#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>
using std::cout;
using std::endl;
using std::thread;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::recursive_mutex;
using std::lock_guard;
#define Lock recursive_mutex

double f(double a)
{
	return (4.0 / (1.0 + a * a));
}

class BruteForceThread
{
	int myN, myFrom, myTo;
	double myH, mySum, * sum_ptr;
	thread myThread;
	Lock* lock_ptr;

public:
	BruteForceThread()
		: myH(0), myN(0), myFrom(0), myTo(0), mySum(0), sum_ptr(nullptr), myThread(), lock_ptr(nullptr) {}

	BruteForceThread(double h, int n, int from, int to, double* sum, Lock* lock)
		: myH(h), myN(n), myFrom(from), myTo(to), mySum(0), sum_ptr(sum), myThread(), lock_ptr(lock) {}

	void start() {
		myThread = thread([this]() {
			lock_guard<Lock> LockGuard(*lock_ptr);
			for (int i = myFrom; i <= myTo; i++)
			{
				double x = myH * ((double)i - 0.5);
				mySum += f(x);
			}
			*sum_ptr += mySum;

			//cout << "Thread " << std::this_thread::get_id() << " sum: " << mySum * myH << endl;
			});
	}

	void join() {
		myThread.join();
	}

private:

};

int main(int argc, char* argv[])
{
	double total_time;

	double PI25DT = 3.141592653589793238462643;
	double pi, h, sum, x;
	double* local_sum;
	int i;

	int numThreads = thread::hardware_concurrency();


	if (argc != 2) {
		printf("Usage : %s <number_of_intervals>\n", argv[0]);
		return 1;
	}

	long int n = strtol(argv[1], NULL, 10);
	pi = 0.0;
	h = 1.0 / (double)n;
	sum = 0.0;

	time_point<steady_clock> start = steady_clock::now();

	Lock lock;
	int block = n / numThreads;
	int from = 0;
	int to = 0;

	BruteForceThread* threads = new BruteForceThread[numThreads];

	for (int i = 0; i < numThreads; ++i)
	{
		from = i * block;
		to = from + block;
		if (i == (numThreads - 1)) to = n;
		threads[i] = BruteForceThread(h, n, from, to, &sum, &lock);
		threads[i].start();
	}

	// wait for threads to terminate            
	for (int i = 0; i < numThreads; ++i) {
		try {
			threads[i].join();
		}
		catch (std::exception e) {}
	}
	pi = h * sum;

	total_time = duration_cast<milliseconds>(steady_clock::now() - start).count();
	printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
	printf("Total time (s): %f\n", total_time / 1000);


	return 0;
}