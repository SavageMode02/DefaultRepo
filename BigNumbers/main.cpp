#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>


class BigNumbers
{
public:
	BigNumbers() = default;
	BigNumbers(const std::string& s)
		:num(Convert(s)){}


	std::string ToString() const;

	static std::vector<int> Convert(const std::string& s);

	static BigNumbers Add(const BigNumbers& s1, const BigNumbers& s2);

	static std::vector<int> Substract(const std::string& s1, const std::string& s2);

private:
	std::vector<int> num;
	bool isPositive = true;
	static const int chunkLength;
};

const int BigNumbers::chunkLength = 1;

std::string BigNumbers::ToString() const 
{
	if (num.empty()) { return "0"; }
	std::ostringstream oss;
	oss << *num.crbegin();
	for (auto id = num.crbegin() + 1; id != num.crend(); id++)
	{
		std::string t = std::to_string(*id);
		oss << std::string(chunkLength - t.size(), '0') << t;
	}
	return oss.str();
}

std::vector<int> BigNumbers::Convert(const std::string& s)
{
	size_t pos = s.size() ;
	std::vector <int> result;
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
	return result;
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
	for (auto id = 0; id <= n1.num.size() - 1; id++)
	{
		int sum = n1.num.at(id) + n2.num.at(id) + sumBack;
		sumBack = floor(sum / 10);
		result.num.push_back(sum % 10);
		if (id == n1.num.size() - 1 && sum > 9)
		{
			result.num.push_back(sumBack);
		}
	}
	return result;
}

std::vector<int> BigNumbers::Substract(const std::string& str1, const std::string& str2)
{
	std::vector<int> n1 = Convert(str1);
	std::vector<int> n2 = Convert(str2);
	if (n1.size() > n2.size())
	{
		n2.insert(n2.end(), n1.size() - n2.size(), 0);
	}
	if (n1.size() < n2.size())
	{
		n1.insert(n1.end(), n2.size() - n1.size(), 0);
	}
	std::vector<int> result(n1.size(), 0);
	int subBack = 0;
	for (auto id = 0; id <= n1.size() - 1; id++)
	{
		if (n1.at(id) - n2.at(id) - subBack >= 0)
		{
			result.at(id) = n1.at(id) - n2.at(id) - subBack;
			subBack = 0;
		}
		else
		{
			result.at(id) = n1.at(id) - n2.at(id) - subBack + 10;
			subBack = 1;
		}
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
											{"183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202"});
	std::cout << SumResult.ToString();
	std::vector <int> SubResult = BigNumbers::Substract("1838928384844400338440392294003393902029393333302930029302019230392290302923930209293200200209392002332202", "183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202");
	for (auto id = 0; id < SubResult.size(); id++)
	{
		std::cout << SubResult.at(SubResult.size() - id - 1);
	}

}