/*
 * 2.13
 * 	Αρχικά θα εκτυπωθούν οι σειρές:
 * 		Thread 0 n = 1  a[0] =1
 * 		Thread 1 n = 2  a[1] =2
 * 		Thread 2 n = 3  a[2] =3
 * 		Thread 3 n = 4  a[3] =4
 *  αλλά με τυχαία σειρά αφού εκτυπώνονται από διαφορετικά threads
 *  που τρέχουν ταυτόχρονα. Ίσως ακόμα να εμπλακούν μεταξύ τους,
 *  αν η εκτύπωση μιας thread ξεκινήσει πριν τελείωσει αυτή μιας άλλης.
 *
 *  Τέλος θα εκτυπωθούν οι σειρές:
 *  	a[0] = 1
 * 		a[1] = 2
 * 		a[2] = 3
 * 		a[3] = 4
 * 		n = 10
 * 	έτσι όπως εμφανίζονται εδώ.
 *
 * 2.15
 * 	Τα αποτελέσματα συμφώνουν με τις εκτιμήσεις μου.
 *  Ο πίνακας a έχει αυτές τις τιμέςεπειδή είναι public ιδιότητα της count,
 *  η οποία μοιράζεται ως αναφορά, άρα επηρεάζεται από όλα τα threads.
 *  Η n ισούται με το άθροισμα των threadN όλων των στιγμιοτύπων CounterThread,
 *  το οποιό υπολογίζεται στο κύριο thread.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

class SharedCounter {
public:
	int n; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	int* a; //Μεταβλητή αντικειμένων || Δεν μοιράζεται

	SharedCounter()
		: n(0), a(nullptr) {};

	SharedCounter(int numThreads) { //numThreads Όρισμα τιμής

		this->n = 0;
		this->a = new int[numThreads]; //Dynamic resizable array

		for (int i = 0; i < numThreads; i++) //i Τοπική εκτός της main || Δεν μοιράζεται
			this->a[i] = 0;
	}

};

class CounterThread {

	int threadID; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	SharedCounter threadCount; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	thread myThread; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	
public:
	int threadN; //Μεταβλητή αντικειμένων || Δεν μοιράζεται

	CounterThread()
		: threadID(-1), threadN(0), threadCount() {}

	CounterThread(int tid, SharedCounter& c) { //tid, c Ορίσματα τιμής. Pass counter by reference
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

	int numThreads = 4; //Τοπική στη main || Δεν μοιράζεται

	SharedCounter count(numThreads); //Τοπική στη main || Μοιράζεται ως όρισμα αναφοράς

	CounterThread *counterThreads = new CounterThread[numThreads]; //Τοπική στη main || Δεν μοιράζεται
	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Μοιράζεται ως όρισμα τιμής – κάθε νήμα λαμβάνει άλλη τιμή
		counterThreads[i] = CounterThread(i, count);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Δεν μοιράζεται
		try {
			counterThreads[i].join();
			count.n = count.n + counterThreads[i].threadN;
		}
		catch (std::exception e) {}
	}
	for (int i = 0; i < numThreads; i++) //i Τοπική στη main || Δεν μοιράζεται
		cout << "a[" << i << "] = " << count.a[i] << endl;

	cout << "n = " << count.n << endl;
}