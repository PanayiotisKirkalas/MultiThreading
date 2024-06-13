#pragma once
#ifndef REPLY_HPP
#define REPLY_HPP

#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
using namespace std;

class Reply
{
public:
	Reply();
	Reply(string op, float n);
	void setOpcode(string op);
	void setValue(float n);
	string getOpcode();
	float getValue();
private:
	string opcode;
	float num;

	// Grant access to Boost.Serialization
	friend class boost::serialization::access;

	// Define the serialize method
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& opcode;
		ar& num;
	}
};

#endif // REPLY_HPP