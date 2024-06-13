#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include "barrierIncludes.h"
#include "testThread.h"
using namespace std;


int main(int argc, char* argv[]) {
    int numThreads = 2;

    if (argc != 2) {
        cout << "Usage: ./barrierMain <number of threads>" << endl;
        return 1;
    }

    try {
        numThreads = stoi(argv[1]);
    }
    catch (const invalid_argument& e) {
        cout << "Integer argument expected" << endl;
        return 1;
    }

    Barrier testBarrier(numThreads);

    testThread* threads = new testThread[numThreads];
    for (int i = 0; i < numThreads; i++) {
        threads[i] = testThread(i, &testBarrier);
        threads[i].start();
    }

    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    return 0;
}
