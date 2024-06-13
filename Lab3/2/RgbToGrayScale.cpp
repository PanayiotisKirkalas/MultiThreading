#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
using std::thread;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::time_point;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::vector;

int width;

class MyRGBtoScaleThread
{
	int myStride;
	int myPadding;
	int myfrom, myto;
	thread myThread;
	vector<unsigned char>::iterator itrData;

	// constructor
public:

	MyRGBtoScaleThread()
		:myfrom(-1), myto(0), myStride(0), myPadding(0) {}
	MyRGBtoScaleThread(vector<unsigned char>* data, int from, int to, int stride, int padding)
	{
		myfrom = from;
		myto = to;
		itrData = data->begin() + (from) * width * 3;
		myStride = stride;
		myPadding = padding;
	}

	// thread code
	void start()
	{
		myThread = thread([this]() {
			for (int i = myfrom; i < myto; ++i) {
				for (int j = 0; j < width; ++j) {
					unsigned char* pixel = &(*itrData); // Pixel pointer points to the current position
					unsigned char gray = pixel[0] * 0.299 + pixel[1] * 0.587 + pixel[2] * 0.114;
					pixel[0] = pixel[1] = pixel[2] = gray;
					std::advance(itrData, 3);
				}
				std::advance(itrData, 3);
			}
		});
	}

	void join() {
		myThread.join();
	}
};

void main() {
	ifstream ifs("original.bmp", ios::in | ios::binary);
	ofstream ofs("result.bmp", ios::out | ios::binary);
	vector<unsigned char> buffer;
	int numThreads = thread::hardware_concurrency();

	time_point<steady_clock> start = steady_clock::now();

	ifs.seekg(0, ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(0, ios::beg);

	buffer.reserve(size);
	buffer.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	ifs.close();
	ofs.write(reinterpret_cast<const char*>(buffer.data()), 54);

	width = *(int*)&buffer[18];
	int height = abs(*(int*)&buffer[22]);
	int stride = (width * 3 + 3) & ~3;
	int padding = stride - width * 3;
	buffer.erase(buffer.begin(), buffer.begin() + 54);

	cout << "width: " << width << " (" << width * 3 << ")" << endl;
	cout << "height: " << height << endl;
	cout << "stride: " << stride << endl;
	cout << "padding: " << padding << endl;


	//  Static block partitioning
	int block = height / numThreads;
	int from = 0;
	int to = 0;

	// thread creation
	MyRGBtoScaleThread* threads = new MyRGBtoScaleThread[numThreads];

	// thread execution   
	for (int i = 0; i < numThreads; ++i)
	{
		from = i * block;
		to = from + block;
		if (i == (numThreads - 1)) to = height;
		threads[i] = MyRGBtoScaleThread(&buffer, from, to, stride, padding);
		threads[i].start();
	}

	// wait for threads to terminate       
	double elapsedTimeMillis;
	for (int i = 0; i < numThreads; ++i) {
		try {
			threads[i].join();
		}
		catch (std::exception e) {}
	}
	ofs.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

	// get current time and calculate elapsed time
	elapsedTimeMillis = duration_cast<milliseconds>(steady_clock::now() - start).count();
	cout << "time in ms = " << elapsedTimeMillis << endl;
}