/*
 * 2.13
 * 	Αρχικά θα εκτυπωθούν οι σειρές:
 * 		Thread 0 my a = 0
 * 		Thread 1 my a = 1
 * 		Thread 2 my a = 2
 * 		Thread 3 my a = 3
 *  με τυχαία σειρά αφού εκτυπώνονται από διαφορετικά threads
 *  που εκτελούνται ταυτόχρονα. Ίσως ακόμα να εμπλακούν μεταξύ τους,
 *  αν η εκτύπωση μιας thread ξεκινήσει πριν τελείωσει αυτή μιας άλλης.
 *
 *  Τέλος θα εκτυπωθούν οι σειρές:
 *  	n = 0
 *  	a[0] = 0
 *  	a[1] = 1
 *  	a[2] = 2
 *  	a[3] = 3
 * 	έτσι όπως εμφανίζονται εδώ.
 *
 * 2.15
 * 	Τα αποτελέσματα συμφώνουν με τις εκτιμήσεις μου.
 *  Το n παραμένει 0, επειδή μοιράζεται ως όρισμα τιμής, δηλαδή κάθε thread
 *  αντιγράφει την τιμή του σε μια άλλη μεταβλήτη και δουλεύει με αυτήν,
 *  αντί να κάνει ότι αλλαγές χρειάζεται στο ίδιο.
 *  Ο πίνακας a έχει τις τιμές που έχει επειδή είναι μοιράζεται ως όρισμα αναφοράς,
 *  άρα επηρεάζεται από όλα τα threads.
 */

#include <iostream>
#include <thread>
using std::cout;
using std::endl;
using std::thread;

class CounterThread {

	int threadID; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	int n; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	int* a; //Μεταβλητή αντικειμένων || Δεν μοιράζεται
	thread myThread; //Μεταβλητή αντικειμένων || Δεν μοιράζεται

public:
	CounterThread() 
		: n(0), a(nullptr), threadID(-1), myThread() {};

	CounterThread(int tid, int n, int* a) { //tid, n Ορίσματα τιμής - a Όρισμα αναφοράς
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

	int numThreads = 4; //Τοπική στη main || Δεν μοιράζεται

	int n = 0; //Τοπική στη main || Μοιράζεται ως όρισμα τιμής – όλα τα νήματα λαμβάνουν την ίδια τιμή
	int *a = new int[numThreads]; //Τοπική στη main || Μοιράζεται ως όρισμα αναφοράς
	for (int i = 0; i < numThreads; i++) //i Τοπική στη main || Δεν μοιράζεται
		a[i] = 0;

	CounterThread* counterThreads = new CounterThread[numThreads]; //Τοπική στη main || Δεν μοιράζεται
	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Μοιράζεται ως όρισμα τιμής – κάθε νήμα λαμβάνει άλλη τιμή
		counterThreads[i] = CounterThread(i, n, a);
		counterThreads[i].start();
	}

	for (int i = 0; i < numThreads; i++) { //i Τοπική στη main || Δεν μοιράζεται
		try {
			counterThreads[i].join();
		}
		catch (std::exception e) {}
	}

	cout << "n = " << n << endl;

	for (int i = 0; i < numThreads; i++) //i Τοπική στη main || Δεν μοιράζεται
		cout << "a[" << i << "] = " << a[i] << endl;

	return 0;
}

