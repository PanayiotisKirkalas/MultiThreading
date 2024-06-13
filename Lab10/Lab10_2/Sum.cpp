#include "Sum.h"

Sum::Sum(int init)
	:myInit(init), result(-1) {}

void Sum::addTo(double f)
{
	lock_guard<recursive_mutex> guard(lock);
	result += f;
}

void Sum::printResult() const
{
	cout << "Result = " << result << endl;
}

void Sum::printInit() const
{
	cout << "Initial = " << myInit << endl;
}

int Sum::getInit() const
{
	return myInit;
}

double Sum::getResult() const
{
	return result;
}
