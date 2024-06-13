/*
 * 2.13
 * 	������ �� ���������� �� ������:
 * 		Thread 0 n = 1
 * 		Thread 1 n = 2
 * 		Thread 2 n = 3
 * 		Thread 3 n = 4
 *  �� ������ ����� ���� ������������ ��� ����������� threads
 *  ��� ����������� ����������. ���� ����� �� ��������� ������ ����,
 *  �� � �������� ���� thread ��������� ���� ��������� ���� ���� �����.
 *
 *  ����� �� ����������:
 *  	Main n = 10
 *
 * 2.15
 * 	�� ������������ ��������� �� ��� ���������� ���.
 *  � n ������� �� �� �������� ��� threadN ���� ��� ������������ CounterThread,
 *  �� ����� ������������ ��� ����� thread.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

class CounterThread {

	int threadID; //��������� ������������ || ��� ����������
	thread myThread; //��������� ������������ || ��� ����������
public:
	int threadN;  //��������� ������������ || ��� ����������

	CounterThread()
		:threadID(-1), threadN(0), myThread() {}

	CounterThread(int tid, int n) { //tid, n �������� �����
		this->threadID = tid;
		this->threadN = n;
	}

	void start() {
		myThread = thread([this]() {
			threadN = threadN + 1 + threadID;
			cout << "Thread " << threadID << " n = " << threadN << endl;
		});
	}

	void join() {
		myThread.join();
	}
};

void main() {

	int numThreads = 4; //������ ��� main || ��� ����������

	int n = 0; //������ ��� main || ���������� �� ������ ����� � ��� �� ������ ��������� ��� ���� ����
	CounterThread *counterThreads = new CounterThread[numThreads]; //������ ��� main || ��� ����������
	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ���������� �� ������ ����� � ���� ���� �������� ���� ����
		counterThreads[i] = CounterThread(i, n);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i ������ ��� main
		try {
			counterThreads[i].join();
			n += counterThreads[i].threadN;
		}
		catch (std::exception e) {}
	}
	cout << "Main n = " << n << endl;
}
