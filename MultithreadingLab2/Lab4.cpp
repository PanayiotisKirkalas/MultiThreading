/*
 * 2.13
 * 	Αρχικά θα εκτυπωθούν οι σειρές:
 * 		Thread 0 n = 1
 * 		Thread 1 n = 2
 * 		Thread 2 n = 3
 * 		Thread 3 n = 4
 *  με τυχαία σειρά αφού εκτυπώνονται από διαφορετικά threads
 *  που εκτελούνται ταυτόχρονα. Ίσως ακόμα να εμπλακούν μεταξύ τους,
 *  αν η εκτύπωση μιας thread ξεκινήσει πριν τελείωσει αυτή μιας άλλης.
 *
 *  Τέλος θα εμφανιστεί:
 *  	Main n = 10
 *
 * 2.15
 * 	Τα αποτελέσματα συμφώνουν με τις εκτιμήσεις μου.
 *  Η n ισούται με το άθροισμα των threadN όλων των στιγμιοτύπων CounterThread,
 *  το οποιό υπολογίζεται στο κύριο thread.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

class CounterThread {

	int threadID; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	thread myThread; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
public:
	int threadN;  //Μεταβλητή αντικειμένων || Δεν μοιράζεται

	CounterThread()
		:threadID(-1), threadN(0), myThread() {}

	CounterThread(int tid, int n) { //tid, n Ορίσματα τιμής
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

	int numThreads = 4; //Τοπική στη main || Δεν μοιράζεται

	int n = 0; //Τοπική στη main || Μοιράζεται ως όρισμα τιμής – όλα τα νήματα λαμβάνουν την ίδια τιμή
	CounterThread *counterThreads = new CounterThread[numThreads]; //Τοπική στη main || Δεν μοιράζεται
	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Μοιράζεται ως όρισμα τιμής – κάθε νήμα λαμβάνει άλλη τιμή
		counterThreads[i] = CounterThread(i, n);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main
		try {
			counterThreads[i].join();
			n += counterThreads[i].threadN;
		}
		catch (std::exception e) {}
	}
	cout << "Main n = " << n << endl;
}
