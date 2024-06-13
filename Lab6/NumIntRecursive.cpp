//Conclusion from observation: 4 to 5 threads seems to be the best

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>
using namespace std;
using namespace chrono;
#define Lock recursive_mutex

double f(double a)
{
	return (4.0 / (1.0 + a * a));
}

class RecursiveThread
{
	int myFrom, myTo, myLimit;
	double myH, mySum, * sum_ptr;
	thread myThread;
	Lock* lock_ptr;

public:
	RecursiveThread()
		: myH(0), myFrom(0), myTo(0), myLimit(0), mySum(0), sum_ptr(nullptr), myThread(), lock_ptr(nullptr) {}

	RecursiveThread(double h, int from, int to, int limit, double* sum, Lock* lock)
		: myH(h), myFrom(from), myTo(to), myLimit(limit), mySum(0), sum_ptr(sum), myThread(), lock_ptr(lock) {}

	void start() {
		myThread = thread([this]() {
			int workload = myTo - myFrom;
			if (workload <= myLimit) {
				for (int i = myFrom; i <= myTo; i++)
				{
					double x = myH * ((double)i - 0.5);
					mySum += f(x);
				}
				{
					lock_guard<Lock> LockGuard(*lock_ptr);
					*sum_ptr += mySum;
				}
			}
			else {
				int mid = myFrom + workload / 2;
				RecursiveThread* threadL = new RecursiveThread(myH, myFrom, mid, myLimit, sum_ptr, lock_ptr);
				threadL->start();
				RecursiveThread* threadR = new RecursiveThread(myH, mid, myTo, myLimit, sum_ptr, lock_ptr);
				threadR->start();

				threadL->join();
				threadR->join();
				delete threadL, threadR;
			}

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
	int limit;
	double PI25DT = 3.141592653589793238462643;
	double pi, h, sum, x;
	double* local_sum;

	if (argc != 2) {
		printf("Usage : %s <number_of_intervals>\n", argv[0]);
		return 1;
	}

	long int n = strtol(argv[1], NULL, 10);
	pi = 0.0;
	h = 1.0 / (double)n;
	sum = 0.0;
	limit = n / 4;

	time_point<steady_clock> start = steady_clock::now();

	Lock lock;

	RecursiveThread* threads = new RecursiveThread(h, 0, n, limit, &sum, &lock);
	threads->start();

	// wait for threads to terminate            
	try {
		threads->join();
	}
	catch (std::exception e) {}
	pi = h * sum;

	total_time = duration_cast<milliseconds>(steady_clock::now() - start).count();
	printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
	printf("Total time (s): %f\n", total_time / 1000);


	return 0;
}