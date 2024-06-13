#pragma once
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
using namespace std;

class Request
{
public:
	Request();
	Request(string op, float n1, float n2);
	string getOpcode();
	float getFirst();
	float getSecond();

private:
	string opcode;
	float num1, num2;

	// Grant access to Boost.Serialization
	friend class boost::serialization::access;

	// Define the serialize method
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& opcode;
		ar& num1;
		ar& num2;
	}
};

#endif // !REQUEST_HPP
