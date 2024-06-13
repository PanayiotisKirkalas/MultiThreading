#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <string>
using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    int size = 0;
    if (argc != 2) {
        cout << "Usage: <exe> <size>" << endl;
        return 1;
    }

    size = stoi(argv[1]);

    if (size <= 0) {
        cout << "Size should be a positive integer" << endl;
        return 1;
    }

    vector<bool> prime(size + 1, true);

    auto start = high_resolution_clock::now();

    int limit = sqrt(size) + 1;
    for (int p = 2; p <= limit; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= size; i += p)
                prime[i] = false;
        }
    }

    auto end = high_resolution_clock::now();
    double duration = duration_cast<chrono::milliseconds>(end - start).count();

    int count = 0;
    for (int i = 2; i <= size; i++) {
        if (prime[i] == true) {
            count++;
        }
    }

    cout << "Number of primes: " << count << endl;
    cout << "Time in ms: " << duration << endl;

    return 0;
}
