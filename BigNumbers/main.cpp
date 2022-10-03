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

	static std::vector<int> Convert(const std::string& s);

	bool PositiveCheck(const std::string& s) const;

	static BigNumbers Add(const BigNumbers& s1, const BigNumbers& s2);

	static BigNumbers Add1(const BigNumbers& n1, const BigNumbers& n2);

	static BigNumbers Substract(const BigNumbers& sub1, const BigNumbers& sub2);

	static BigNumbers Substract1(const BigNumbers& n1, const BigNumbers& n2);

private:
	std::vector<int> num;
	bool isPositive = true;
	static const int chunkLength;
};

const int BigNumbers::chunkLength = 8;

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
	size_t pos = s.size();
	if (s.at(0) == '-')
	{
		while (pos >= chunkLength + 1)
		{
			pos -= chunkLength;
			std::string t = s.substr(pos, chunkLength);
			result.push_back(std::stoi(t));
		}
		if (pos != 1)
		{
			std::string t = s.substr(1, pos);
			result.push_back(std::stoi(t));
		}
	}
	else
	{
		while (pos >= chunkLength)
		{
			pos -= chunkLength;
			std::string t = s.substr(pos, chunkLength);
			result.push_back(std::stoi(t));
		}
		if (pos != 0)
		{
			std::string t = s.substr(0, pos);
			result.push_back(std::stoi(t));
		}
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


BigNumbers BigNumbers::Add(const BigNumbers& s1, const BigNumbers& s2)
{
	auto n1 = s1;
	auto n2 = s2;
	if (n1.num.size() > n2.num.size())
	{
		//		while(s1.num.size() != s2.num.size())
		n2.num.insert(n2.num.end(), n1.num.size() - n2.num.size(), 0);
	}
	if (n1.num.size() < n2.num.size())
	{
		n1.num.insert(n1.num.end(), n2.num.size() - n1.num.size(), 0);
	}
	BigNumbers result;
	int sumBack = 0;
	for (auto id = 0; id <= n1.num.size() - chunkLength; id+=chunkLength)
	{
		auto vechunk1 = 0;
		auto vechunk2 = 0;
		for (auto i = 0; i <= chunkLength - 1; i++)
		{
			vechunk1 += n1.num.at(id + i) * pow(10, i);
			vechunk2 += n2.num.at(id + i) * pow(10, i);
		}

		int sum = vechunk1 + vechunk2 + sumBack;
		sumBack = floor(sum / pow(10, chunkLength+1));
		auto intores = sum - sumBack * intPower(10, chunkLength + 1);
		for (int id = 0; id < chunkLength; id++)
		{
			auto currentDigit = chunkLength - id ;
			auto digit = floor( intores % intPower(10, currentDigit + 1) / intPower(10, currentDigit));
			result.num.push_back(digit);
		}
	}
	auto remain = n1.num.size() % chunkLength;
	if (remain != 0)
	{ 
		for (auto id = n1.num.size() - remain; id <= n1.num.size() - 1; id++)
		{
			int sum = n1.num.at(id) + n2.num.at(id) + sumBack;
			sumBack = floor(sum / 10);
			result.num.push_back(sum % 10);
			if (id == n1.num.size() - 1 && sum > 9)
			{
				result.num.push_back(sumBack);
			}
		}
	}

	return result;
}

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

BigNumbers BigNumbers::Add1(const BigNumbers& n1,const BigNumbers& n2)
{
	auto l1 = n1;
	auto l2 = n2;
	BigNumbers result;
	if (l1.isPositive && l2.isPositive)
	{
		result = Add(l1, l2);
	}
	if (!l1.isPositive && l2.isPositive)
	{
		l1.isPositive = true;
		result = Substract(l2, l1);
	}
	if (l1.isPositive && !l2.isPositive)
	{
		l2.isPositive = true;
		result = Substract(l1, l2);
	}
	if (!l1.isPositive && !l2.isPositive)
	{
		l1.isPositive = true;
		l2.isPositive = true;
		result = Add(l1, l2);
		result.isPositive = false;
	}
	return result;
}


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


int main()
{
	BigNumbers number("123456789123456789123456789123456789");
	std::cout << number.ToString() << std::endl;
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

}