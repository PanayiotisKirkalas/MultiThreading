#include "Request.h"

Request::Request()
	:opcode(), num1(0), num2(0) {}

Request::Request(string op, float n1, float n2) {
	opcode = op;
	num1 = n1;
	num2 = n2;
}

string Request::getOpcode() {
	return opcode;
}

float Request::getFirst() {
	return num1;
}

float Request::getSecond() {
	return num2;
}
