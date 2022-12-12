#include <vector>
#pragma once

using namespace std;

class X10Mess
{
public:
	X10Mess();
	//~X10Mess();
	void addTwoBits(bool conditional);
	void addVibbleChar(uint8_t newchar);
	void addVibbleNum(uint8_t newchar);
	void addFooter();
	void getX10ContentsPtr(char *& X10ContentsPtr);
private:
	vector<char> X10Contents_;
	uint8_t lastWrittenBitSet_;
};
