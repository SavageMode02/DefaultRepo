#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>


class BigNumbers
{
public:
	BigNumbers(const std::string& s)
		:num(Convert(s)){}


	std::string ToString() const;

	static std::vector<int> Convert(const std::string& s);

	static std::vector<int> Add(std::string s1, std::string s2);

	static std::vector<int> Substract(std::string s1, std::string s2);

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

std::vector<int> BigNumbers::Add(std::string s1, std::string s2)
{
	std::vector<int> num1 = Convert(s1);
	std::vector<int> num2 = Convert(s2);
	if (num1.size() > num2.size())
	{
		num2.insert(num2.end(), num1.size() - num2.size(), 0);
	}
	if (num1.size() < num2.size())
	{
		num1.insert(num1.end(), num2.size() - num1.size(), 0);
	}
	std::vector<int> result(num1.size(), 0);
	int sumBack = 0;
	for (auto id = 0; id <= num1.size() - 1; id++)
	{
		int sum = num1.at(id) + num2.at(id) + sumBack;
		sumBack = floor(sum / 10);
		result.at(id) = sum % 10;
		if (id == num1.size() - 1 && sum > 9)
		{
			result.insert(result.end(), sumBack);
		}
	}
	return result;
}

std::vector<int> BigNumbers::Substract(std::string str1, std::string str2)
{
	std::vector<int> n1 = Convert(str1);
	std::vector<int> n2 = Convert(str2);
	std::vector<int> result(n1.size(), 0);
	if (n1.size() > n2.size())
	{
		n2.insert(n2.end(), n1.size() - n2.size(), 0);
	}
	if (n1.size() < n2.size())
	{
		n1.insert(n1.end(), n2.size() - n1.size(), 0);
	}
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
	std::cout <<"123456789123456789123456789123456789" << std::endl;
	BigNumbers number1("123456789123456700000000000000089123456000000000000000000333332344340000000000000789123456789");
	std::cout << number1.ToString() << std::endl;
	std::cout << "123456789123456700000000000000089123456000000000000000000333332344340000000000000789123456789" << std::endl;
	std::cout << "111111111111122222222223333333123333333333333321112222"<<std::endl;
	std::cout << "18389283848444003384403922940033939020293933333029300293020192303922903029239302092932002002093920023322020209876 " << std::endl;
	std::cout << "183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202" << std::endl;
	std::vector <int> SumResult = BigNumbers::Add("18389283848444003384403922940033939020293933333029300293020192303922903029239302092932002002093920023322020209876", "183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202");
	for (auto id = 0; id < SumResult.size(); id++)
	{
		std::cout << SumResult.at(SumResult.size() - id - 1);
	}
	std::vector <int> SubResult = BigNumbers::Substract("1838928384844400338440392294003393902029393333302930029302019230392290302923930209293200200209392002332202 ", "183892838484440032374738466338328303393902029393333003040403332211203922903029239339493494030049393233220202");
	for (auto id = 0; id < SubResult.size(); id++)
	{
		std::cout << SubResult.at(SubResult.size() - id - 1);
	}

}