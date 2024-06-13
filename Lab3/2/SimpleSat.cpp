#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
using std::cout;
using std::endl;
using std::thread;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::time_point;

// Circuit input size (number of bits)
const int size = 28;


// Printing utility
void printResult(bool* v, int z) {
    cout << z;
    for (int i = 0; i < size; i++)
        if (v[i]) cout << " 1";
        else cout << " 0";
    cout << endl;
}

void check_circuit(int z) {

    // z: the combination number
    // v: the combination number in binary format 

    bool v[size];

    for (int i = size - 1; i >= 0; i--)
        v[i] = (z & (1 << i)) != 0;

    // Check the ouptut of the circuit for input v
    bool value =
        (v[0] || v[1])
        && (!v[1] || !v[3])
        && (v[2] || v[3])
        && (!v[3] || !v[4])
        && (v[4] || !v[5])
        && (v[5] || !v[6])
        && (v[5] || v[6])
        && (v[6] || !v[15])
        && (v[7] || !v[8])
        && (!v[7] || !v[13])
        && (v[8] || v[9])
        && (v[8] || !v[9])
        && (!v[9] || !v[10])
        && (v[9] || v[11])
        && (v[10] || v[11])
        && (v[12] || v[13])
        && (v[13] || !v[14])
        && (v[14] || v[15])
        && (v[14] || v[16])
        && (v[17] || v[1])
        && (v[18] || !v[0])
        && (v[19] || v[1])
        && (v[19] || !v[18])
        && (!v[19] || !v[9])
        && (v[0] || v[17])
        && (!v[1] || v[20])
        && (!v[21] || v[20])
        && (!v[22] || v[20])
        && (!v[21] || !v[20])
        && (v[22] || !v[20]);

    // If output == 1 print v and z
    if (value) {
        printResult(v, z);
    }

    //delete v;
}

class MySimpleSatThread {
    thread myThread;
    int myfrom, myto;

public:
    MySimpleSatThread()
        : myThread(), myfrom(-1), myto(0) {}

    MySimpleSatThread(int from, int to) {
        myfrom = from;
        myto = to;
    }

    void start() {
        myThread = thread([this]() {
            for (int i = myfrom; i < myto; ++i)
                check_circuit(i);
        });
    }

    void join() {
        myThread.join();
    }
};

int main() {
    int numThreads = thread::hardware_concurrency();
    // Number of possible inputs (bit combinations)
    int iterations = (int)std::pow(2, size);

    // Start timing
    time_point<steady_clock> start = steady_clock::now();

    // thread creation
    MySimpleSatThread* threads = new MySimpleSatThread[numThreads];

    //  Static block partitioning
    int block = iterations / numThreads;
    int from = 0;
    int to = 0;

    // thread execution   
    for (int i = 0; i < numThreads; ++i)
    {
        from = i * block;
        to = from + block;
        if (i == (numThreads - 1)) to = iterations;
        threads[i] = MySimpleSatThread(from, to);
        threads[i].start();
    }

    // wait for threads to terminate
    for (int i = 0; i < numThreads; ++i) {
        try {
            threads[i].join();
        }
        catch (std::exception e) {}
    }

    // Stop timing   
    double elapsedTimeMillis = duration_cast<milliseconds>(steady_clock::now() - start).count();

    cout << "All done\n" << endl;
    cout << "time in ms = " << elapsedTimeMillis << endl;

    return 0;
}