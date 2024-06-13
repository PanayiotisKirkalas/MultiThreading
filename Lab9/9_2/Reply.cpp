#include "Reply.h"

Reply::Reply()
	: opcode(), num(0) {}

Reply::Reply(string op, float n)
	: opcode(std::move(op)), num(n) {}

void Reply::setOpcode(string op)
{
	opcode = std::move(op);
}

void Reply::setValue(float n)
{
	num = n;
}

string Reply::getOpcode()
{
	return opcode;
}

float Reply::getValue()
{
	return num;
}



