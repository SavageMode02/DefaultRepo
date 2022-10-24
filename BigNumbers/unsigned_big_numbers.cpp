#include "unsigned_big_numbers.h"
#include <sstream>

const int UBigNumbers::chunkLength = 3;
const int UBigNumbers::maxChunkPlusOne = pow(10, chunkLength);

bool isAllDigits(const std::string& s)
{
	for (char c : s)
	{
		if (!(c >= '0' && c <= '9'))
			return false;
	}
	return true;
}

std::string dropFirstZeros(const std::string& s)
{
	std::string r;
	bool isFirstZeros = true;
	for (char c : s)
	{
		if (c == '0' && isFirstZeros)
			continue;
		else
			isFirstZeros = false;
		r += c;
	}
	return r;
}

UBigNumbers::UBigNumbers(const std::string& s)
{
	if (!isAllDigits(s))
	{
		throw new std::invalid_argument(s);
	}
	auto s1 = dropFirstZeros(s);
	size_t pos = s1.size();
	while (pos >= chunkLength)
	{
		pos -= chunkLength;
		num.push_front(std::stoi(s1.substr(pos, chunkLength)));
	}
	if (pos != 0)
	{
		num.push_front(std::stoi(s1.substr(0, pos)));
	}
}

UBigNumbers::UBigNumbers(uint64_t s)
{
	while (s != 0)
	{
		num.push_front(s % maxChunkPlusOne);
		s = s / maxChunkPlusOne;
	}
}


std::string UBigNumbers::ToString() const
{
	if (num.empty()) { return "0"; }
	std::ostringstream oss;

	oss << *num.cbegin();
	for (auto id = num.cbegin() + 1; id != num.cend(); id++)
	{
		std::string t = std::to_string(*id);
		if (t.size() > chunkLength)
			oss << t;
		else
			oss << std::string(chunkLength - t.size(), '0') << t;
	}
	return oss.str();
}

bool UBigNumbers::operator==(const UBigNumbers& val) const
{
	if (num.size() != val.num.size())
		return false;
	for (size_t i = 0; i < num.size(); i++)
	{
		if (num[i] != val.num[i])
			return false;
	}
	return true;
}


bool UBigNumbers::operator>(const UBigNumbers& val) const
{
	if (num.size() >= val.num.size())
	{
		for (size_t i = num.size() - 1; i >= 0; i--)
		{
			if (i >= val.num.size() && num[i] != 0)
				return true;
			if (i < val.num.size() && num[i] != val.num[i])
				return num[i] > val.num[i];
		}
		return false;
	}
	return !(val > *this);
}


bool UBigNumbers::operator<(const UBigNumbers& val) const
{
	return !(*this > val || val == *this);
}

UBigNumbers UBigNumbers::Add(const UBigNumbers& s1, const UBigNumbers& s2)
{
	auto result = s1;
	int p = 0;
	int val = 0;
	for (size_t i = 0; i < s2.num.size(); i++)
	{
		if (i >= result.num.size())
		{
			result.num.push_back(0);
		}
		val = result.num[i] + s2.num[i] + p;
		result.num[i] = val % maxChunkPlusOne;
		p = val / maxChunkPlusOne;
		if (p > 0 && i + 1 >= result.num.size())
		{
			result.num.push_back(p);
			p = 0;
		}
	}
	//	if (p > 0)
	//	{
	//		result.num.back() += p;
	//	}
	return result;
}

UBigNumbers UBigNumbers::Sub(const UBigNumbers& s1, const UBigNumbers& s2) 
{
	auto result = s1;
	for (size_t i = 0; i < s2.num.size(); i++)
	{
		if (result.num[i] < s2.num[i])
		{
			int j = i + 1;
			while (result.num[j] == 0)
			{
				j++;
			}
			while (j > i)
			{
				result.num[j]--;
				j--;
				result.num[j] += maxChunkPlusOne;
			}
		}
		result.num[i] -= s2.num[i];
	}
	return result;
}

UBigNumbers UBigNumbers::Mul(const UBigNumbers& s1, const UBigNumbers& s2)
{
	UBigNumbers result("0");
	for (UBigNumbers i = { "0" }; i < s2; i = Add(i, { "1" }))
	{
		//std::cout << i.ToString() << std::endl;
		result = Add(result, s1);
	}
	return result;
}