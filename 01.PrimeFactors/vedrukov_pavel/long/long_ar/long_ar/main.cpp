#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include "BigInt.h"
#include <fstream>
using namespace std;

bool factor(BigInt a)
{
	BigInt zero("0");
	BigInt two("2");
	BigInt one("1");
	BigInt i("2");
	BigInt end = a;
	int result = 0;
	while (a % i == zero)
	{
		a = a / i;
		result++;
	}
	i = i + one;
	while (a % i == zero)
	{
		a = a / i;
		result++;
	}

	for (i = "5"; i * i <= a; i = i + two)
	{
		while (a % i == zero)
		{
			a = a / i;
			result++;
		}
		if (a == one)
		{
			break;
		}
	}
	if (result == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void main()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	ifstream fin("C:\\composite9.in.txt");
	ofstream fout;
	fout.open("C:\\Users\\1222965\\comp.txt");
	BigInt Nums(9);
	bool result;
	for (int i = 0; i < 100; i++)
	{
		fin >> Nums;
		start = std::chrono::system_clock::now();
		result = factor(Nums);
		end = std::chrono::system_clock::now();
		cout << i << " ";
		int elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>
			(end - start).count();
		if (result)
		{
			fout << '-' << elapsed_seconds << endl;
		}
		else
		{
			fout << elapsed_seconds << endl;
		}
	}
	fin.close();
	fout.close();
	system("pause");
}