/*
 * 2.13
 * 	������ �� ���������� �� ������:
 * 		Thread 0 my a = 0
 * 		Thread 1 my a = 1
 * 		Thread 2 my a = 2
 * 		Thread 3 my a = 3
 *  �� ������ ����� ���� ������������ ��� ����������� threads
 *  ��� ����������� ����������. ���� ����� �� ��������� ������ ����,
 *  �� � �������� ���� thread ��������� ���� ��������� ���� ���� �����.
 *
 *  ����� �� ���������� �� ������:
 *  	n = 0
 *  	a[0] = 0
 *  	a[1] = 1
 *  	a[2] = 2
 *  	a[3] = 3
 * 	���� ���� ������������ ���.
 *
 * 2.15
 * 	�� ������������ ��������� �� ��� ���������� ���.
 *  �� n ��������� 0, ������ ���������� �� ������ �����, ������ ���� thread
 *  ���������� ��� ���� ��� �� ��� ���� ��������� ��� �������� �� �����,
 *  ���� �� ����� ��� ������� ���������� ��� ����.
 *  � ������� a ���� ��� ����� ��� ���� ������ ����� ���������� �� ������ ��������,
 *  ��� ����������� ��� ��� �� threads.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

class CounterThread {

	int threadID; //��������� ������������ || ��� ����������
	int n; //��������� ������������ || ��� ����������
	int* a; //��������� ������������ || ��� ����������
	thread myThread; //��������� ������������ || ��� ����������

public:
	CounterThread() 
		: n(0), a(nullptr), threadID(-1), myThread() {};

	CounterThread(int tid, int n, int* a) { //tid, n �������� ����� - a ������ ��������
		threadID = tid;
		this->n = n; //"this->" because the member has the same name as the parameter
		this->a = a; //"this->" because the member has the same name as the parameter
	}

	void start() {
		myThread = thread([this]() {
			n = n + threadID;
			a[threadID] = a[threadID] + n;
			cout << "Thread " << threadID << " my a = " << a[threadID] << endl;
			});
	}

	void join() {
		myThread.join();
	}
};

int main() {

	int numThreads = 4; //������ ��� main || ��� ����������

	int n = 0; //������ ��� main || ���������� �� ������ ����� � ��� �� ������ ��������� ��� ���� ����
	int *a = new int[numThreads]; //������ ��� main || ���������� �� ������ ��������
	for (int i = 0; i < numThreads; i++) //i ������ ��� main || ��� ����������
		a[i] = 0;

	CounterThread* counterThreads = new CounterThread[numThreads]; //������ ��� main || ��� ����������
	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ���������� �� ������ ����� � ���� ���� �������� ���� ����
		counterThreads[i] = CounterThread(i, n, a);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ��� ����������
		try {
			counterThreads[i].join();
		}
		catch (std::exception e) {}
	}

	cout << "n = " << n << endl;

	for (int i = 0; i < numThreads; i++) //i ������ ��� main || ��� ����������
		cout << "a[" << i << "] = " << a[i] << endl;

	return 0;
}

