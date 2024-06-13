#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: BruteForceStringMatch <file name> <pattern>" << endl;
		return 1;
	}

	time_point<steady_clock> start = high_resolution_clock::now();

	ifstream file(argv[1]);
	if (!file.is_open()) {
		cerr << "Error opening file." << endl;
		return 1;
	}

	string fileString((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
	int n = fileString.length();

	string patternString(argv[2]);
	int m = patternString.length();

	int matchLength = n - m;
	string match(matchLength, '0');
	int matchCount = 0;

	/*cout << "File size: " << fileString.length() << endl;
	cout << "Pattern size: " << patternString.length() << endl;
	cout << "match size: " << matchLength << endl;*/

	for (int j = 0; j < matchLength; j++) {
		int i;
		for (i = 0; i < m && patternString[i] == fileString[i + j]; i++);
		if (i >= m) {
			match[j] = '1';
			matchCount++;
		}
	}

	double duration = duration_cast<milliseconds>(high_resolution_clock::now() - start).count();

	for (int i = 0; i < matchLength; i++) {
		if (match[i] == '1') cout << i << " ";
	}
	cout << endl;
	cout << "Total matches: " << matchCount << endl;
	cout << "Time in ms: " << duration << endl;

	return 0;
}
