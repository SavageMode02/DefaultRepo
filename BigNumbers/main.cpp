#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>
#define intPower

class BigNumbers
{
public:
	BigNumbers() = default;
	BigNumbers(const std::string& s)
		:num(Convert(s)) 
		,isPositive(PositiveCheck(s)) {}


	std::string ToString() const;

	bool operator>(const BigNumbers& val) const;
	bool operator<=(const BigNumbers& val) const { return !(*this > val); }

	bool PositiveCheck(const std::string& s) const;


	static BigNumbers Add(const BigNumbers& n1, const BigNumbers& n2);
	static BigNumbers Sub(const BigNumbers& n1, const BigNumbers& n2);

//	static BigNumbers Substract(const BigNumbers& sub1, const BigNumbers& sub2);

//	static BigNumbers Substract1(const BigNumbers& n1, const BigNumbers& n2);

private:
	static std::vector<int> Convert(const std::string& s);
	static BigNumbers Add_(const BigNumbers& s1, const BigNumbers& s2);
	static BigNumbers Sub_(const BigNumbers& s1, const BigNumbers& s2);

	bool isUnsignedBigest(const BigNumbers& val) const;
private:
	std::vector<int> num;
	bool isPositive = true;
	static const int chunkLength;
	static const int maxChunkPlusOne;
};

const int BigNumbers::chunkLength = 3;
const int BigNumbers::maxChunkPlusOne = pow(10, chunkLength);

bool BigNumbers::operator>(const BigNumbers& val) const
{
	if (val.isPositive != isPositive)
	{
		if (isPositive)
			return true;
		return false;
	}
	return isUnsignedBigest(val);
}

bool BigNumbers::isUnsignedBigest(const BigNumbers& val) const
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
	return !val.isUnsignedBigest(*this);
}

std::string BigNumbers::ToString() const
{
	if (num.empty()) { return "0"; }
	std::ostringstream oss;
	if (!isPositive)
	{
		oss << "-";
	}
	oss << *num.crbegin();
	for (auto id = num.crbegin() + 1; id != num.crend(); id++)
	{
		std::string t = std::to_string(*id);
		if (t.size() > chunkLength)
			oss << t;
		else
			oss << std::string(chunkLength - t.size(), '0') << t;
	}
	return oss.str();
}

std::vector<int> BigNumbers::Convert(const std::string& s)
{
	std::vector<int> result;
	std::string t = s;
	if (s.at(0) == '-' || s.at(0) == '+')
		t = s.substr(1, s.size());
	size_t pos = t.size();
	while (pos >= chunkLength)
	{
		pos -= chunkLength;
		std::string t1 = t.substr(pos, chunkLength);
		result.push_back(std::stoi(t1));
	}
	if (pos != 0)
	{
		std::string t1 = t.substr(0, pos);
		result.push_back(std::stoi(t1));
	}
	return result;
}


bool BigNumbers::PositiveCheck(const std::string& s) const
{
	if (s.at(0) == '-')
	{
		return false;
	}
	else
	{
		return true;
	}
}

BigNumbers BigNumbers::Sub_(const BigNumbers& s1, const BigNumbers& s2)
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

BigNumbers BigNumbers::Add_(const BigNumbers& s1, const BigNumbers& s2)
{
	auto result = s1;
	int p = 0;
	int val = 0;
	for (size_t i = 0; i<s2.num.size(); i++)
	{
		if (i > result.num.size())
			result.num.push_back(0);
		val = result.num[i] + s2.num[i] + p;
		result.num[i] = val % maxChunkPlusOne;
		p = val / maxChunkPlusOne;
	}
	return result;
}
/*
BigNumbers BigNumbers::Substract(const BigNumbers& sub1, const BigNumbers& sub2)
{
	auto n1 = sub1;
	auto n2 = sub2;
	BigNumbers result;
	if (n1.num.size() > n2.num.size())
	{
		n2.num.insert(n2.num.end(), n1.num.size() - n2.num.size(), 0);
	}
	if (n1.num.size() < n2.num.size())
	{
		n1.num.insert(n1.num.end(), n2.num.size() - n1.num.size(), 0);
		result.isPositive = false;
	}
	if (n1.num.size() == n2.num.size())
	{
		for (auto id = 0; id < n1.num.size(); id++)
		{
			if (n1.num.at(id) > n2.num.at(id))
			{
				break;
			}
			if (n1.num.at(id) < n2.num.at(id))
			{
				result.isPositive = false;
				break;
			}
		}
	}
	int subBack = 0;
	if (!result.isPositive)
	{
		auto vechunk1 = 0;
		auto vechunk2 = 0;
		for (auto id = 0; id <= n1.num.size() - chunkLength; id += chunkLength)
		{
			for (auto i = 0; i <= chunkLength - 1; i++)
			{
				vechunk1 += n1.num.at(id + i) * pow(10, i);
				vechunk2 += n2.num.at(id + i) * pow(10, i);
			}
			int sub = vechunk2 - vechunk1 - subBack;
			if (sub < 0)
			{
				sub += intPower(10, chunkLength + 1);
				subBack++;
			}
			else
			{
				subBack = 0;
			}
			for (int id = 0; id < chunkLength; id++)
			{
				auto currentDigit = chunkLength - id;
				auto digit = floor(sub % intPower(10, currentDigit + 1) / intPower(10, currentDigit));
				result.num.push_back(digit);
			}
		}
		auto remain = n1.num.size() % chunkLength;
		if (remain != 0)
		{
			for (auto id = n1.num.size() - remain; id <= n1.num.size() - 1; id++)
			{
				int sub= n2.num.at(id) - n1.num.at(id) - subBack;
				if (sub < 0)
				{
					sub += 10;
					subBack++;
				}
				else
				{
					subBack = 0;
				}
				result.num.push_back(sub);
			}
		}

	}
	if (result.isPositive)
	{
		auto vechunk1 = 0;
		auto vechunk2 = 0;
		for (auto id = 0; id <= n1.num.size() - chunkLength; id += chunkLength)
		{
			for (auto i = 0; i <= chunkLength - 1; i++)
			{
				vechunk1 += n1.num.at(id + i) * pow(10, i);
				vechunk2 += n2.num.at(id + i) * pow(10, i);
			}
			int sub = vechunk1 - vechunk2 - subBack;
			if (sub < 0)
			{
				sub += intPower(10, chunkLength + 1);
				subBack++;
			}
			for (int id = 0; id < chunkLength; id++)
			{
				auto currentDigit = chunkLength - id;
				auto digit = floor(sub % intPower(10, currentDigit + 1) / intPower(10, currentDigit));
				result.num.push_back(digit);
			}
		}
		auto remain = n1.num.size() % chunkLength;
		if (remain != 0)
		{
			for (auto id = n1.num.size() - remain; id <= n1.num.size() - 1; id++)
			{
				int sub = n1.num.at(id) - n2.num.at(id) - subBack;
				if (sub < 0)
				{
					sub += 10;
					subBack++;
				}
				else
				{
					subBack = 0;
				}
				result.num.push_back(sub);
			}
		}

	}

	return result;
}

*/
BigNumbers BigNumbers::Add(const BigNumbers& n1,const BigNumbers& n2)
{
	BigNumbers result;
	if (n1.isPositive == n2.isPositive) 
	{
		result = Add_(n1, n2);
	}
	else if(n1.isUnsignedBigest(n2))
	{
		result = Sub_(n1, n2);
		result.isPositive = n1.isPositive;
	}
	else
	{
		result = Sub_(n2, n1);
		result.isPositive = n2.isPositive;
	}
	return result;
}

BigNumbers BigNumbers::Sub(const BigNumbers& n1, const BigNumbers& n2)
{
	auto l2 = n2;
	l2.isPositive = !l2.isPositive;
	return Add(n1, l2);
}


/*
BigNumbers BigNumbers::Substract1(const BigNumbers& n1, const BigNumbers& n2)
{
	auto l1 = n1;
	auto l2 = n2;
	BigNumbers result;
	if (l1.isPositive && l2.isPositive)
	{
		result = Substract(l1, l2);
	}
	if (!l1.isPositive && l2.isPositive)
	{
		l1.isPositive = true;
		result = Add(l1, l2);
		result.isPositive = false;
	}
	if (l1.isPositive && !l2.isPositive)
	{
		l2.isPositive = true;
		result = Add(l1, l2);
	}
	if (!l1.isPositive && !l2.isPositive)
	{
		l2.isPositive = true;
		result = Substract(l2, l1);
	}
	return result;
}
*/


int main()
{
	BigNumbers number("123456789123456789123456789123456789");
	//std::cout << number.ToString() << std::endl;
	BigNumbers r1 = BigNumbers::Add({ "5356" }, { "6356" });  
	std::cout << (r1.ToString() == "11712")<<std::endl;
	BigNumbers r2 = BigNumbers::Add({ "-5356" }, { "-6356" });
	std::cout << (r2.ToString() == "-11712")<<std::endl;

	BigNumbers r3 = BigNumbers::Add({ "5356" }, { "-6356" });
	std::cout << (r3.ToString() == "-1000") << std::endl;
	BigNumbers r4 = BigNumbers::Add({ "-5356" }, { "6356" });
	std::cout << (r4.ToString() == "1000") << std::endl;

	BigNumbers r5 = BigNumbers::Sub({ "5356" }, { "6356" });
	std::cout << (r5.ToString() == "-1000") << std::endl;
	BigNumbers r6 = BigNumbers::Sub({ "5000356" }, { "6356" });
	std::cout << r6.ToString() << std::endl;
	std::cout << (r6.ToString() == "4994000") << std::endl;


	/*
	std::cout << "123456789123456789123456789123456789" << std::endl;
	BigNumbers number1("123456789123456700000000000000089123456000000000000000000333332344340000000000000789123456789");
	std::cout << number1.ToString() << std::endl;
	std::cout << "123456789123456700000000000000089123456000000000000000000333332344340000000000000789123456789" << std::endl;
	std::cout << "111111111111122222222223333333123333333333333321112222" << std::endl;
	std::cout << "18389283848444003384403922940033939020293933333029300293020192303922903029239302092932002002093920023322020209876 " << std::endl;
	std::cout << "183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202" << std::endl;
	BigNumbers SumResult = BigNumbers::Add(BigNumbers("18389283848444003384403922940033939020293933333029300293020192303922903029239302092932002002093920023322020209876"),
		{ "183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202" });
	std::cout << SumResult.ToString();
	BigNumbers SubResult = BigNumbers::Substract(BigNumbers("1838928384844400338440392294003393902029393333302930029302019230392290302923930209293200200209392002332202"),
														BigNumbers("183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202"));
	std::cout << SubResult.ToString();
	*/

}