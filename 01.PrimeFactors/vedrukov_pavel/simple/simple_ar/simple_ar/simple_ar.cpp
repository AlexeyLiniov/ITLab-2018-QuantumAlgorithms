#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

bool prime(unsigned long long int n)
{
	int i = 2, j = 3;
	char flag = 0;
	while (n % i != 0)
	{
		n /= i;
		flag++;
	}
	while (n % j != 0)
	{
		n /= j;
		flag++;
	}
	for (i = 5, j = 7; i*i <= n, j*j <= n; j += 6, i += 6)
	{
		while (n % i != 0)
		{
			n /= i;
			flag++;
		}
		while (n % j != 0)
		{
			n /= j;
			flag++;
		}
	}
	if (flag == 0)
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
	ifstream fin("C:\\composite15.in.txt");
	ofstream fout;
	fout.open("C:\\Users\\1222965\\comp.txt");
	unsigned long long int Nums;
	bool result;
	for (int i = 0; i < 100; i++)
	{
		fin >> Nums;
		start = std::chrono::system_clock::now();
		result = prime(Nums);
		end = std::chrono::system_clock::now();
		cout << i << " ";
		int elapsed_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>
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