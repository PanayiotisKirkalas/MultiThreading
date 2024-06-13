#include <iostream>
#include <thread>

void f(int i) {
	for (int j = 1; j <= 20; ++j) {
		std::cout << "Thread: " << i << " = " << j * i << std::endl;
	}
}

int main() {
	std::thread threads[10]; //Standard threads

	for (int i = 0; i < 10; ++i) {
		threads[i] = std::thread(f, i + 1); //We can just pass a function pointer to them
		                                                 //and the function's parameters. We don't always 
														 //have to wrap them
	}

	for (int i = 0; i < 10; ++i) {
		threads[i].join();                         //Wait for threads to finish
	}

	return 0;
}