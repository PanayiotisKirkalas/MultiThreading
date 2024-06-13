#pragma once
#include <iostream>
#include <string>
#include <mutex>
using namespace std;
class Sum
{
	int myInit;
	double result;
	recursive_mutex lock;
public:
	Sum(int init);
	void addTo(double f);
	void printResult() const;
	void printInit() const;
	int getInit() const;
	double getResult() const;
};

