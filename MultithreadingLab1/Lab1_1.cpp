#include <iostream>
#include <thread>

//Thread wrapper class A
//The thread is wrapped because in C++, unlike Java
//inheriting build-in classes is not recommended
class A {
	std::thread t;

public:
	//Default constructor (no arguments)
	A()
	: t{} {}

	//Destructor. It is called when the objects gets out of scope,
	//and waits for the thread to finish
	~A() {
		t.join();
	}

	//It calls a separate thread to print two messages
	//with a one second delay between them
	void run() {
		t = std::thread([]() {//lambda function
			std::cout << "Thread 1" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Thread 1 again" << std::endl;
		});
	}
};

//Thread wrapper class B
//The thread is wrapped because in C++, unlike Java
//inheriting build-in classes is not recommended
class B {
	std::thread t;
	int id;

public:
	//Regural constructor
	//No default constructor
	B(int x)
		: t{}, id(x) {}

	//Destructor. It is called when the objects gets out of scope,
	//and waits for the thread to finish
	~B() {
		t.join();
	}

	//It calls a separate thread to print a message
	//The thread is wrapped because in C++, unlike Java
	//inheriting build-in classes is not recommended
	void run() {
		t = std::thread([this]() { //lambda function. We "capture" "this", meaning the current object, so it can use it's members
			std::cout << "Thread " << id << std::endl;
			});
	}
};

int main() {
	A a[10];																//No need to initialize them because it has a default constructor
	B b[10] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }; //We can't leave them unitialized because they don't have a default constructor

	for (int i = 0; i < 10; ++i) {
		a[i].run();
		b[i].run();
	}

	return 0;
}