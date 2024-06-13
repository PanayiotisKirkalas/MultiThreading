#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#define Lock recursive_mutex

using namespace std;
using namespace std::chrono;

class StaticThread
{
	int myFrom, myTo, myM, * count_ptr;
	string* pattern_str_ptr, * file_str_ptr, * match_ptr;
	thread myThread;
	Lock* lock_ptr;

public:
	StaticThread()
		: myFrom(0), myTo(0), myM(0), count_ptr(nullptr), pattern_str_ptr(nullptr), file_str_ptr(nullptr), match_ptr(nullptr), myThread(), lock_ptr(nullptr) {}

	StaticThread(int from, int to, int m, int *count, string* pattern, string* file, string* match, Lock* lock)
		: myFrom(from), myTo(to), myM(m), count_ptr(count), pattern_str_ptr(pattern), file_str_ptr(file), match_ptr(match), myThread(), lock_ptr(lock) {}

	void start() {
		myThread = thread([this]() {
			for (int j = myFrom; j <= myTo; j++)
			{
				int i;
				for (i = 0; i < myM && (*pattern_str_ptr)[i] == (*file_str_ptr)[i + j]; i++);
				//cout << "Thread: " << this_thread::get_id() << " iterations: " << i << endl;
				if (i >= myM) {
					lock_guard<Lock> LockGuard(*lock_ptr);
					(*match_ptr)[j] = '1';
					(*count_ptr)++;
				}
			}

			//cout << "Thread " << std::this_thread::get_id() << " sum: " << mySum * myH << endl;
			});
	}

	void join() {
		myThread.join();
	}
};

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: BruteForceStringMatch <file name> <pattern>" << endl;
		return 1;
	}

	int numThreads = thread::hardware_concurrency();

	time_point<steady_clock> start = high_resolution_clock::now();

	ifstream file(argv[1]);
	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
		return 1;
	}

	string fileString((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
	int n = fileString.length();

	string patternString(argv[2]);
	int m = patternString.length();

	int matchLength = n - m;
	string match(matchLength, '0');
	int matchCount = 0;

	Lock lock;
	int block = matchLength / numThreads;
	int from = 0;
	int to = 0;

	StaticThread* threads = new StaticThread[numThreads];

	/*cout << "File size: " << fileString.length() << endl;
	cout << "Pattern size: " << patternString.length() << endl;
	cout << "match size: " << matchLength << endl;*/

	for (int i = 0; i < numThreads; ++i)
	{
		from = i * block;
		to = from + block;
		if (i == (numThreads - 1)) to = matchLength;
		threads[i] = StaticThread(from, to, m, &matchCount, &patternString, &fileString, &match, &lock);
		threads[i].start();
	}

	// wait for threads to terminate            
	for (int i = 0; i < numThreads; ++i) {
		try {
			threads[i].join();
		}
		catch (std::exception e) {}
	}

	/*for (int j = 0; j < matchLength; j++) {
		int i;
		for (i = 0; i < m && patternString[i] == fileString[i + j]; i++);
		if (i >= m) {
			match[j] = '1';
			matchCount++;
		}
	}*/

	double duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();

	for (int i = 0; i < matchLength; i++) {
		if (match[i] == '1') cout << i << " ";
	}
	cout << endl;
	cout << "Total matches: " << matchCount << endl;
	cout << "Time in ms: " << duration << endl;

	return 0;
}
