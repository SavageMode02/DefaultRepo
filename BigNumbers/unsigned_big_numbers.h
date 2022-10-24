#pragma once

#include<iostream>
#include<deque>
#include<string>

class UBigNumbers
{
public:
	UBigNumbers() : UBigNumbers((uint64_t)0) {}
	UBigNumbers(const std::string& s);
	UBigNumbers(uint64_t s);
	UBigNumbers(int64_t s) : UBigNumbers((uint64_t)(abs(s))) {}

	std::string ToString() const;

	bool operator>(const UBigNumbers& val) const;
	bool operator<(const UBigNumbers& val) const { return !(*this > val || val == *this); }
	bool operator<=(const UBigNumbers& val) const { return !(*this > val); }
	bool operator>=(const UBigNumbers& val) const { return !(*this < val); }
	bool operator==(const UBigNumbers& val) const;
	bool operator!=(const UBigNumbers& val) const { return !(*this == val); }
	void operator++();
	static UBigNumbers Add(const UBigNumbers& n1, const UBigNumbers& n2);
	static UBigNumbers Sub(const UBigNumbers& n1, const UBigNumbers& n2);
	static UBigNumbers Mul(const UBigNumbers& n1, const UBigNumbers& n2);
	static UBigNumbers Div(const UBigNumbers& n1, const UBigNumbers& n2);

private:
	std::deque<int> num;
	static const int chunkLength;
	static const int maxChunkPlusOne;
};