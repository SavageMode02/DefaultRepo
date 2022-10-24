#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>
#include "unsigned_big_numbers.h"

bool ConstructUnsignedNums()
{
	UBigNumbers a("00000000000000000000000120031234343");
	uint64_t t = 312999988998888899;
	UBigNumbers b(t);
	uint64_t t1 = 312999988998888899;
	UBigNumbers c(t1);
	bool r1 = (a.ToString() == "120031234343");
	bool r2 = (b.ToString() == "312999988998888899");
	bool r3 = (c.ToString() == "312999988998888899");
	return r1 && r2 && r3;
}

bool EqualsUnsignedNums()
{
	UBigNumbers a("00000000000000000000000120031234343");
	UBigNumbers b(312999988998888899);
	UBigNumbers d(312999988998888899);
	UBigNumbers c(912999988998888899);
	bool r1 = (b == d);
	bool r2 = !(b != d);
	bool r3 = (b > a);
	bool r4 = (c > b);
	bool r5 = (b < c);
	bool r6 = (c >= b);
	bool r7 = (b <= c);
	bool r8 = (b <= d) && (b >= d);
	return r1 && r2 && r3 && r4
		&& r5 && r6 && r7 && r8;
}

bool AddUnsignedTest()
{
	uint64_t t = 312999988998888899;
	UBigNumbers a(t);
	UBigNumbers b(t);
	bool result1 = (UBigNumbers::Add(a, b) == UBigNumbers("625999977997777798"));
	uint64_t t1 = 312999988998888899;
	uint64_t t2 = 912999988998888899;
	UBigNumbers a1(t1);
	UBigNumbers b1(t2);
	bool result2 = (UBigNumbers::Add(a1, b1) == UBigNumbers("1225999977997777798"));
	UBigNumbers t3 = UBigNumbers::Add(a1, b1);
	UBigNumbers t4 = UBigNumbers::Add(a1, t3);
	bool result3 = (UBigNumbers::Add(t3, t4) == UBigNumbers("2764999944994444495"));
	return result1 && result2 && result3;
}

bool SubUnsignedTest()
{
	uint64_t t = 312999988998888899;
	UBigNumbers a(t);
	UBigNumbers b(t);
	bool result1 = (UBigNumbers::Sub(a, b) == UBigNumbers("0"));
	uint64_t t1 = 3199988998888899;
	uint64_t t2 = 912999988998888899;
	UBigNumbers a1(t1);
	UBigNumbers b1(t2);
	bool result2 = (UBigNumbers::Sub(b1, a1) == UBigNumbers("909800000000000000"));
	bool result3 = (UBigNumbers::Sub(a1, b1) == UBigNumbers("909800000000000000"));
	return result1 && result2 && result3;
}

bool MulUnsignedTest()
{
	uint64_t t = 312999988998888899;
	UBigNumbers a(t);
	bool result1 = (UBigNumbers::Mul(a, UBigNumbers("100")) == UBigNumbers("31299998899888889900"));
	bool result2 = (UBigNumbers::Mul(a, UBigNumbers("1")) == UBigNumbers("312999988998888899"));
	UBigNumbers b("111111");
	bool result3 = (UBigNumbers::Mul(a, UBigNumbers("0")) == UBigNumbers("0"));
	bool result4 = (UBigNumbers::Mul(b, b) == UBigNumbers("12345654321"));
	return result1 && result2 && result3 && result4;
}

int main()
{
	std::cout << "ConstructUnsignedNums():" << ConstructUnsignedNums() << std::endl;
	std::cout << "EqualsUnsignedNums():" << EqualsUnsignedNums() << std::endl;
	std::cout << "AddUnsignedTest():" << AddUnsignedTest() << std::endl;
	std::cout << "SubUnsignedTest():" << SubUnsignedTest() << std::endl;
	std::cout << "MulUnsignedTest():" << MulUnsignedTest() << std::endl;
}