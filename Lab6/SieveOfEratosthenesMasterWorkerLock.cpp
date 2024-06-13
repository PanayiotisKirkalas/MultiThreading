#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <string>
using namespace std;
using namespace chrono;
#define Lock recursive_mutex
#define ID_TEST(x) {lock_guard<Lock> guard(*lock_ptr);if (myId == x) cout << std::dec << "Thread " << myId << " test" << endl;}
#define TASK_TEST(x) {lock_guard<Lock> guard(*lock_ptr);if (1) cout << std::dec << "Thread " << myId << " element " << element << endl;}
#define correct 5761455

int totalTasks; // αριθμός εργασιών
int tasksAssigned = 1; // διαμοιραζόμενη μεταβλητή μετρητή εργασιών 
int limit;

Lock globalLock;

// Κρίσιμo τμήμα για την διανομή εργασιών
int getTask()
{
    lock_guard<recursive_mutex> guard(globalLock);
    // Διανέμει μια εργασία (στοιχείο πίνακα) 
	if (++tasksAssigned < limit) {
		/*if (tasksAssigned == totalTasks - 1)
			cout << "Thread " << this_thread::get_id() << " final task" << endl;*/
		return tasksAssigned;
	}
    else
        return -1;
}

class WorkerThread
{
	int myId, myTotalTasks;
	bool* prime_ptr;
	thread myThread;
	Lock* lock_ptr;

public:
	WorkerThread()
		: myId(-1), myTotalTasks(-1), prime_ptr(nullptr), myThread(), lock_ptr(nullptr) {}

	WorkerThread(int id, int p_totalTasks, bool* prime, Lock* lock = nullptr)
		: myId(id), myTotalTasks(p_totalTasks), prime_ptr(prime), myThread(), lock_ptr(lock) {}

	void start() {
		myThread = thread([this]() {
			int error = 0;
			/*{
				lock_guard<Lock> guard(*lock_ptr);
				cout << "Thread: " << std::hex << this_thread::get_id() << endl;
				cout << "\t" << myIndex << endl;
				cout << "\t" << myLimit << endl;
				cout << "\t" << myThreadN << endl;
			}*/

			int element, counter = 0;
			//lock_guard<Lock> guard(*lock_ptr);
			while ((element = getTask()) >= 0) {
				if (prime_ptr[element]) {
					for (int i = element * element; i <= myTotalTasks; i += element) {
						//lock_guard<Lock> guard(*lock_ptr);
						prime_ptr[i] = false;
						error += prime_ptr[i];
					}
				}
			}
			/*{
				lock_guard<Lock> guard(*lock_ptr);
				cout << dec << "Thread " << myId << " Errors: " << error << endl;
			}*/
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

	totalTasks = stoi(argv[1]);
	int numThreads = thread::hardware_concurrency();

	if (totalTasks <= 0) {
		cout << "size should be a positive integer" << std::endl;
		return 1;
	}

	//vector<bool> prime(totalTasks + 1, true);
	bool* prime = new bool[totalTasks + 1];
	for (int i = 0; i <= totalTasks; ++i) {
		prime[i] = true;
	}
	Lock localLock;

	// Get current time
	auto start = high_resolution_clock::now();

	limit = static_cast<int>(std::sqrt(totalTasks)) + 1;

	WorkerThread* threads = new WorkerThread[numThreads];

	for (int i = 0; i < numThreads; ++i)
	{
		threads[i] = WorkerThread(i, totalTasks, prime, &localLock);
		threads[i].start();
	}

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
	for (int i = 2; i <= totalTasks; ++i) {
		if (prime[i]) {
			++count;
		}
	}

	//cout << dec << "Difference: " << abs(count - correct) << endl;

	cout << "number of primes " << std::dec << count << std::endl;
	cout << "time in ms = " << elapsedTime << std::endl;

	return 0;
}
