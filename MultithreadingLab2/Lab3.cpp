/*
 * 2.13
 * 	������ �� ���������� �� ������:
 * 		Thread 0 n = 1  a[0] =1
 * 		Thread 1 n = 2  a[1] =2
 * 		Thread 2 n = 3  a[2] =3
 * 		Thread 3 n = 4  a[3] =4
 *  ���� �� ������ ����� ���� ������������ ��� ����������� threads
 *  ��� ������� ����������. ���� ����� �� ��������� ������ ����,
 *  �� � �������� ���� thread ��������� ���� ��������� ���� ���� �����.
 *
 *  ����� �� ���������� �� ������:
 *  	a[0] = 1
 * 		a[1] = 2
 * 		a[2] = 3
 * 		a[3] = 4
 * 		n = 10
 * 	���� ���� ������������ ���.
 *
 * 2.15
 * 	�� ������������ ��������� �� ��� ���������� ���.
 *  � ������� a ���� ����� ��� ����������� ����� public �������� ��� count,
 *  � ����� ���������� �� �������, ��� ����������� ��� ��� �� threads.
 *  � n ������� �� �� �������� ��� threadN ���� ��� ������������ CounterThread,
 *  �� ����� ������������ ��� ����� thread.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

class SharedCounter {
public:
	int n; //��������� ������������ || ��� ����������
	int* a; //��������� ������������ || ��� ����������

	SharedCounter()
		: n(0), a(nullptr) {};

	SharedCounter(int numThreads) { //numThreads ������ �����

		this->n = 0;
		this->a = new int[numThreads]; //Dynamic resizable array

		for (int i = 0; i < numThreads; i++) //i ������ ����� ��� main || ��� ����������
			this->a[i] = 0;
	}

};

class CounterThread {

	int threadID; //��������� ������������ || ��� ����������
	SharedCounter threadCount; //��������� ������������ || ��� ����������
	thread myThread; //��������� ������������ || ��� ����������
	
public:
	int threadN; //��������� ������������ || ��� ����������

	CounterThread()
		: threadID(-1), threadN(0), threadCount() {}

	CounterThread(int tid, SharedCounter& c) { //tid, c �������� �����. Pass counter by reference
		this->threadID = tid;
		this->threadCount = c;
		this->threadN = threadCount.n;

	}

	void start() {
		myThread = thread([this]() {
			threadN = threadN + 1 + threadID;
			threadCount.a[threadID] = threadCount.a[threadID] + 1 + threadID;
			cout << "Thread " << threadID << " n = " << threadN << "  a[" << threadID << "] =" << threadCount.a[threadID] << endl;
		});
	}

	void join() {
		myThread.join();
	}
};

void main() {

	int numThreads = 4; //������ ��� main || ��� ����������

	SharedCounter count(numThreads); //������ ��� main || ���������� �� ������ ��������

	CounterThread *counterThreads = new CounterThread[numThreads]; //������ ��� main || ��� ����������
	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ���������� �� ������ ����� � ���� ���� �������� ���� ����
		counterThreads[i] = CounterThread(i, count);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ��� ����������
		try {
			counterThreads[i].join();
			count.n = count.n + counterThreads[i].threadN;
		}
		catch (std::exception e) {}
	}
	for (int i = 0; i < numThreads; i++) //i ������ ��� main || ��� ����������
		cout << "a[" << i << "] = " << count.a[i] << endl;

	cout << "n = " << count.n << endl;
}