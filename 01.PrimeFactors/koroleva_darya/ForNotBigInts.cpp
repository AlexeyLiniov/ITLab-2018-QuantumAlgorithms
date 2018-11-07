#include "stdafx.h"
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <map>
#include <cmath>
using namespace std;

map <long long, int> factorization(long long x);

int main()
{
	
	ifstream fin("E:\\Git Projects\\inputs_fact\\composite15_in.txt");
	ofstream fout("E:\\Git Projects\\inputs_fact\\composite15_out.txt");

	long long x;

	while (fin >> x)
	{

		auto start = chrono::steady_clock::now();

		map <long long, int> m = factorization(x);

		auto end = chrono::steady_clock::now();
		auto timems = chrono::duration_cast<chrono::nanoseconds>(end - start);

		if (m.size() == 0)
		{
			fout << "+"; //<< x << " ";
		}
		else
		{
			fout << "-"; // << x << " = ";
			/*for (map <long long, int>::const_iterator it = m.begin(); it != m.end(); it++)
			{
				fout << it->first << "^" << it->second << " * ";
			}*/
		}
		fout << timems.count() << "\n"; // << "ms" << endl;
	}

	fin.close();
	fout.close();


	return 0;
	
}

map <long long, int> factorization(long long x)
{
	long long x2 = x;

	map <long long, int> div;
	bool isinmap = false;

	if (x == 1)
	{
		div.insert(make_pair(1, 1));
		return div;
	}

	if (x == 2 || x == 3 || x == 5)
	{
		return div;
	}

	int arr235[] = { 2, 3, 5 };

	for (int i = 0; i < 3; i++)
	{
		while (x % arr235[i] == 0)
		{
			x /= 2;
			if (!isinmap && div.find(arr235[i]) == div.end())
			{
				div.insert(make_pair(arr235[i], 1));
				isinmap = true;
			}
			else
			{
				div[arr235[i]]++;
			}
		}
	}

	int arr[] = { 1, 7, 11, 13, 17, 19, 23, 29 };
	for (int i = 0; i < 8; i++)
	{

		for (long long j = 0; (30 * j + arr[i])*(30 * j + arr[i]) <= x; j++)
		{

			long long d = 30 * j + arr[i];
			if (d == 1) continue;

			isinmap = false;

			while (x % d == 0)
			{
				x /= d;

				if (!isinmap && div.find(d) == div.end())
				{
					div.insert(make_pair(d, 1));
					isinmap = true;
				}
				else
				{
					div[d]++;
				}
			}
		}


	}

	if (x != 1 && x != x2)
	{
		div.insert(make_pair (x, 1));
	}

	return div;

}


