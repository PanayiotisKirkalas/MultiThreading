#include "Consumer.h"

Consumer::Consumer()
	:buff(nullptr), scale(-1), myThread() {}

Consumer::Consumer(Buffer* b, int s) 
	: buff(b), scale(s), myThread() {}

void Consumer::start() {
	myThread = thread([this]() {
		int value;
		while (true) {
			try {
				this_thread::sleep_for(milliseconds(rand() % scale));
			}
			catch (exception e) {
				cout << "Thread " << hex << this_thread::get_id() << dec << " Interrupted" << endl;
			}
			value = buff->get();
		}
	});
}

void Consumer::join()
{
	myThread.join();
}
