#ifndef __BIGINT__H
#define __BIGINT__H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int size = 100;
class BigInt
{
private:
	string pNum;
	int rsize;
	char NumDigit;
public:
	BigInt(int = 100, int = 0);
	BigInt(string);
	BigInt(const BigInt&);
	~BigInt();

	BigInt & zerodelete();

	int realsize();
	char operator[](int);
	void mult10(int);
	void div10(int);

	bool operator==(const BigInt &);
	bool operator!=(const BigInt &);
	bool operator<(const BigInt &);
	bool operator>(const BigInt &);
	bool operator<=(const BigInt &);
	bool operator>=(const BigInt &);

	BigInt & operator=(const BigInt &);
	BigInt & operator=(const string &);
	BigInt operator+(const BigInt &);
	BigInt operator-(const BigInt &);
	BigInt operator*(const BigInt &);
	BigInt operator/(const BigInt &);
	BigInt operator%(const BigInt &);

	BigInt operator+=(const BigInt &);
	BigInt operator-=(const BigInt &);
	BigInt operator*=(const BigInt &);
	BigInt operator/=(const BigInt &);
	BigInt operator%=(const BigInt &);



	friend istream & operator>>(istream & stream, BigInt & oth)
	{
		string s;
		getline(stream, s);
		oth = s;
		return stream;
	}

	friend ostream & operator<<(ostream & stream, const BigInt & oth)
	{
		for (int i = oth.rsize - 1; i >= 0; i--)
		{
			stream.put(oth.pNum[i] + '0');
		}
		return stream;
	}
};
#endif
