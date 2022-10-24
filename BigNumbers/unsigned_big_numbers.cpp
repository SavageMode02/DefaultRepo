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
		for (size_t i = num.size() - 1; i >= 0 && i < num.size(); i--)
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

UBigNumbers UBigNumbers::Add(const UBigNumbers& s1, const UBigNumbers& s2)
{
	if (s1 < s2)
		return Add(s2, s1);
	auto result = s1;
	int p = 0;
	int val = 0;
	for (size_t i = s2.num.size() - 1; i >= 0 && i < s2.num.size(); i--)
	{
		if (i >= result.num.size())
		{
			result.num.push_front(0);
		}
		val = result.num[i] + s2.num[i] + p;
		result.num[i] = val % maxChunkPlusOne;
		p = val / maxChunkPlusOne;
	}
	if (p > 0)
	{
		result.num.push_front(p);
	}
	return result;
}

UBigNumbers UBigNumbers::Sub(const UBigNumbers& s1, const UBigNumbers& s2)
{
	if (s1 == s2)
		return { "0" };
	if (s1 < s2)
		return Sub(s2, s1);
	auto result = s1;
	for (size_t i = s2.num.size() - 1; i >= 0 && i < s2.num.size(); i--)
	{
		if (result.num[i] < s2.num[i])
		{
			int j = i - 1;
			while (result.num[j] == 0)
			{
				j--;
			}
			while (j < i)
			{
				result.num[j]--;
				j++;
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
	for (UBigNumbers i = { "0" }; i < s2; ++i)
	{
		//std::cout << i.ToString() << std::endl;
		result = Add(result, s1);
	}
	return result;
}

void UBigNumbers::operator++()
{
	if (num.size() == 0)
	{
		num.push_front(1);
	}
	else
	{
		num[num.size() - 1]++;
		int p = 0;
		bool isBreaked = false;
		for (size_t i = num.size() - 1; i >= 0 && i < num.size(); i--)
		{
			if (num[i] < maxChunkPlusOne)
			{
				isBreaked = true;
				break;
			}
			int val = num[i];
			num[i] = val % maxChunkPlusOne;
			p = val / maxChunkPlusOne;
		}
		if (!isBreaked && p > 0)
		{
			num.push_front(p);
		}
	}
}