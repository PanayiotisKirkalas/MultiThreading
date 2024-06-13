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
 *  Τα αποτελέσματα αυτά παράγονται επειδή οι γραμμές
 *  	 "Thread Χ n = Υ  a[Χ] = Ζ"
 *  εκτυπώνονται από διαφορετικά threads που εκτελούνται ταυτόχρονα,
 *  ενώ οι γραμμές
 *  	 "a[Χ] = Υ" και "n = Ζ"
 *  εκτυπώνονται όλες από το κύριο thread με μια προκαθορισμένη σειρά.
 *  Ο πίνακας a έχει αυτές τις τιμές επειδή είναι καθολικές μεταβλητές,
 *  άρα επηρεάζονται από όλα τα threads.
 *  Η n ισούται με το άθροισμα των threadN όλων των στιγμιοτύπων CounterThread,
 *  το οποιό υπολογίζεται στο κύριο thread.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

int n = 0; //Μεταβλητή κλάσεων || Μοιράζεται ως καθολική μεταβλητή
int* a; //Μεταβλητή κλάσεων || Μοιράζεται ως καθολική μεταβλητή

class CounterThread {
	thread myThread; //Μεταβλητή αντικειμένων || Δεν μοιράζεται

public:
	int threadID; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	int threadN; //Μεταβλητή αντικειμένων || Δεν μοιράζεται

	//Default constructor
	CounterThread()
		: threadID(-1), threadN(0), myThread() {}

	//Regular constructor
	CounterThread(int tid){ //tid Όρισμα τιμής
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

	int numThreads = 4; //Τοπική στη main || Δεν μοιράζεται

	a = new int[numThreads];

	for (int i = 0; i < numThreads; i++) //i Τοπική στη main || Δεν μοιράζεται
		a[i] = 0;

	//Allocationg in heap, just like Java does by default
	CounterThread* counterThreads = new CounterThread[numThreads]; //Τοπική στη main || Δεν μοιράζεται
	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Μοιράζεται ως όρισμα τιμής – κάθε νήμα λαμβάνει άλλη τιμή
		counterThreads[i] = CounterThread(i);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Δεν μοιράζεται
		try {
			counterThreads[i].join();
			n = n + counterThreads[i].threadN;
		}
		catch (std::exception e) {}
	}
	for (int i = 0; i < numThreads; i++) //i Τοπική στη main || Δεν μοιράζεται
		cout << "a[" << i << "] = " << a[i] << endl;

	cout << "n = " << n << endl;

	return 0;
}