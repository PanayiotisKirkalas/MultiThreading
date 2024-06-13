#include <iostream>
#include <thread>
#include <chrono>
using std::cout;
using std::endl;
using std::thread;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::time_point;

/* Matrix Addition A = B + C                       */

int size = 1000;


class MyRGBtoScaleThread
{
	double** tableA;
	double** tableB;
	double** tableC;
	int myfrom;
	int myto;
	thread myThread;

	// constructor
public:
	MyRGBtoScaleThread()
		: tableA(nullptr), tableB(nullptr), tableC(nullptr), myfrom(-1), myto(-1) {}
	MyRGBtoScaleThread(double** a, double** b, double** c, int from, int to)
	{
		tableA = a;
		tableB = b;
		tableC = c;
		myfrom = from;
		myto = to;
	}

	// thread code
	void start()
	{
		myThread = thread([this]() {
			for (int i = myfrom; i < myto; ++i) {
				for (int j = 0; j < size; ++j) {
					tableA[i][j] = tableB[i][j] + tableC[i][j];
				}
			}
			});
	}

	void join() {
		myThread.join();
	}
};

void main() {
	int numThreads = thread::hardware_concurrency();

	double** a = new double* [size];
	double** b = new double* [size];
	double** c = new double* [size];
	for (int i = 0; i < size; ++i) {
		a[i] = new double[size];
		b[i] = new double[size];
		c[i] = new double[size];
		for (int j = 0; j < size; ++j) {
			a[i][j] = 0.1;
			b[i][j] = 0.3;
			c[i][j] = 0.5;
		}
	}

	// for(int i = 0; i < size; ++i) 
	//     for(int j = 0; j < size; ++j)  
	//         a[i][j] = b[i][j] + c[i][j];

	// // for debugging 
	/*for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j) {
			cout << a[i][j] << " " << endl;
		}*/

	// get current time
	time_point<steady_clock> start = steady_clock::now();

	//  Static block partitioning
	int block = size / numThreads;
	int from = 0;
	int to = 0;

	// thread creation 
	MyRGBtoScaleThread *threads = new MyRGBtoScaleThread[numThreads];

	// thread execution   
	for (int i = 0; i < numThreads; ++i)
	{
		from = i * block;
		to = from + block;
		if (i == (numThreads - 1)) to = size;
		threads[i] = MyRGBtoScaleThread(a, b, c, from, to);
		threads[i].start();
	}

	// wait for threads to terminate            
	for (int i = 0; i < numThreads; ++i) {
		try {
			threads[i].join();
		}
		catch (std::exception e) {}
	}

	// get current time and calculate elapsed time
	double elapsedTimeMillis = duration_cast<milliseconds>(steady_clock::now() - start).count();
	cout << "time in ms = " << elapsedTimeMillis << endl;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}