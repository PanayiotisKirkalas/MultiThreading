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
 *  �� ������������ ���� ���������� ������ �� �������
 *  	 "Thread � n = �  a[�] = �"
 *  ������������ ��� ����������� threads ��� ����������� ����������,
 *  ��� �� �������
 *  	 "a[�] = �" ��� "n = �"
 *  ������������ ���� ��� �� ����� thread �� ��� �������������� �����.
 *  � ������� a ���� ����� ��� ����� ������ ����� ��������� ����������,
 *  ��� ������������ ��� ��� �� threads.
 *  � n ������� �� �� �������� ��� threadN ���� ��� ������������ CounterThread,
 *  �� ����� ������������ ��� ����� thread.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

int n = 0; //��������� ������� || ���������� �� �������� ���������
int* a; //��������� ������� || ���������� �� �������� ���������

class CounterThread {
	thread myThread; //��������� ������������ || ��� ����������

public:
	int threadID; //��������� ������������ || ��� ����������
	int threadN; //��������� ������������ || ��� ����������

	//Default constructor
	CounterThread()
		: threadID(-1), threadN(0), myThread() {}

	//Regular constructor
	CounterThread(int tid){ //tid ������ �����
		threadID = tid;
		threadN = n;
	}

	//Creates a seperate thread
	void start() {
		myThread = thread([this]() {
			threadN = threadN + 1 + threadID;
			a[threadID] = a[threadID] + 1 + threadID;
			cout << "Thread " << threadID << " n = " << threadN << "  a[" << threadID << "] =" << a[threadID] << endl;
		});
	}

	//Function to wait for the thread to finish
	void join() {
		myThread.join();
	}
};

int main() {

	int numThreads = 4; //������ ��� main || ��� ����������

	a = new int[numThreads];

	for (int i = 0; i < numThreads; i++) //i ������ ��� main || ��� ����������
		a[i] = 0;

	//Allocationg in heap, just like Java does by default
	CounterThread* counterThreads = new CounterThread[numThreads]; //������ ��� main || ��� ����������
	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ���������� �� ������ ����� � ���� ���� �������� ���� ����
		counterThreads[i] = CounterThread(i);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i ������ ��� main || ��� ����������
		try {
			counterThreads[i].join();
			n = n + counterThreads[i].threadN;
		}
		catch (std::exception e) {}
	}
	for (int i = 0; i < numThreads; i++) //i ������ ��� main || ��� ����������
		cout << "a[" << i << "] = " << a[i] << endl;

	cout << "n = " << n << endl;

	return 0;
}