#include <iostream>
#include <cmath>
#include <vector>
#include <thread>

class MyThread {
private:
    int myFrom;
    int myTo;
    int size;
    std::vector<bool>* prime;

public:
    MyThread(std::vector<bool>* prime, int size, int limit, int id, int numThreads)
        : prime(prime), size(size) {
        myFrom = id * (limit / numThreads);
        myTo = myFrom + (limit / numThreads);
        if (id == (numThreads - 1)) myTo = limit;
    }

    void operator()() {
        for (int p = myFrom; p <= myTo; p++) {
            if (prime->at(p) == true) {
                for (int i = p * p; i <= size; i += p) {
                    std::cout << i << " ";
                    prime->at(i) = false;
                }
            }
        }
    }
};

int main() {
    int size = 100000000;
    int numThreads = std::thread::hardware_concurrency();

    std::vector<bool> prime(size + 1, true);

    int limit = static_cast<int>(sqrt(size)) + 1;

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(MyThread(&prime, size, limit, i, numThreads));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    int count = 0;
    for (int i = 2; i <= size; i++) {
        if (prime[i] == true) {
            count++;
        }
    }

    std::cout << "number of primes " << count << std::endl;
    return 0;
}
