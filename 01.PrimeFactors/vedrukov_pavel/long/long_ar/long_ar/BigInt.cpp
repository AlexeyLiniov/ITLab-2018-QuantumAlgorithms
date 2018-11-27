#include "BigInt.h"
#include <string>

BigInt::BigInt(int size, int d)
{
	NumDigit = d;
	rsize = size;
	pNum.resize(100);
	for (int i = 0; i < pNum.size(); i++)
	{
		pNum[i] = 0;
	}
}

BigInt::BigInt(string k)
{
	if (k == "0")
	{
		rsize = 0;
	}
	else
	{
		rsize = k.size();
	}
	pNum.resize(100);
	for (int i = 0; i < rsize; i++)
	{
		pNum[i] = k[k.size() - 1 - i] - '0';
	}
	for (int i = rsize; i < pNum.size(); i++)
	{
		pNum[i] = 0;
	}
}

BigInt::BigInt(const BigInt & oth)
{
	NumDigit = oth.NumDigit;
	rsize = oth.rsize;
	pNum = oth.pNum;
}

BigInt::~BigInt()
{
}

BigInt& BigInt::zerodelete()
{

	for (int i = pNum.size() - 1; i >= 0; i--)
	{
		if (pNum[i] == 0)
		{
			pNum.erase(pNum.begin() + i);
		}
		else
		{
			break;
		}
	}
	return *this;
}

int BigInt::realsize()
{
	rsize = 100;
	for (int i = pNum.size() - 1; i >= 0; i--)
	{
		if (pNum[i] == 0)
		{
			rsize--;
		}
		else
		{
			break;
		}
	}
	return rsize;
}

char BigInt::operator[](int pos)
{
	if (pos < 0 || pos >= rsize)
	{
		throw "error operator[]";
	}
	return pNum[pos];
}

void BigInt::mult10(int n)
{
	for (int i = rsize - 1; i >= 0; i--)
	{
		pNum[i + n] = pNum[i];
	}
	for (int i = n - 1; i >= 0; i--)
	{
		pNum[i] = 0;
	}
	rsize += n;
}

void BigInt::div10(int n)
{
	for (int i = n; i < rsize; i++)
	{
		pNum[i - n] = pNum[i];
	}
	for (int i = rsize - 1; i > rsize - 1 - n; i--)
	{
		pNum[i] = 0;
	}
	rsize = realsize();
}

bool BigInt::operator==(const BigInt & oth)
{
	if (realsize() == oth.rsize)
	{
		for (int i = 0; i < rsize; i++)
		{
			if (pNum[i] != oth.pNum[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool BigInt::operator!=(const BigInt & oth)
{
	if (realsize() == oth.rsize)
	{
		for (int i = 0; i < rsize; i++)
		{
			if (pNum[i] != oth.pNum[i])
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

bool BigInt::operator<(const BigInt & oth)
{
	if (realsize() == oth.rsize)
	{
		for (int i = rsize - 1; i >= 0; i--)
		{
			if (pNum[i] < oth.pNum[i])
			{
				return true;
			}
			if (pNum[i] > oth.pNum[i])
			{
				return false;
			}

		}
		return false;
	}
	if (realsize() > oth.rsize)
	{
		return false;
	}
	if (realsize() < oth.rsize)
	{
		return true;
	}
}

bool BigInt::operator>(const BigInt & oth)
{
	if (realsize() == oth.rsize)
	{
		for (int i = rsize - 1; i >= 0; i--)
		{
			if (pNum[i] > oth.pNum[i])
			{
				return true;
			}
			if (pNum[i] < oth.pNum[i])
			{
				return false;
			}

		}
		return false;
	}
	if (realsize() < oth.rsize)
	{
		return false;
	}
	if (realsize() > oth.rsize)
	{
		return true;
	}
}

bool BigInt::operator<=(const BigInt & oth)
{
	if (realsize() == oth.rsize)
	{
		for (int i = rsize - 1; i >= 0; i--)
		{
			if (pNum[i] < oth.pNum[i])
			{
				return true;
			}
			if (pNum[i] > oth.pNum[i])
			{
				return false;
			}

		}
		return true;
	}
	if (realsize() > oth.rsize)
	{
		return false;
	}
	if (realsize() < oth.rsize)
	{
		return true;
	}
}

bool BigInt::operator>=(const BigInt & oth)
{
	if (realsize() == oth.rsize)
	{
		for (int i = rsize - 1; i >= 0; i--)
		{
			if (pNum[i] > oth.pNum[i])
			{
				return true;
			}
			if (pNum[i] < oth.pNum[i])
			{
				return false;
			}

		}
		return true;
	}
	if (realsize() < oth.rsize)
	{
		return false;
	}
	if (realsize() > oth.rsize)
	{
		return true;
	}
}

BigInt & BigInt::operator=(const BigInt & oth)
{
	if (this == &oth)
	{
		return *this;
	}
	else
	{
		pNum = oth.pNum;
		rsize = oth.rsize;
		NumDigit = oth.NumDigit;
		return *this;
	}
}

BigInt & BigInt::operator=(const string & oth)
{
	rsize = oth.size();
	for (int i = 0; i < rsize; i++)
	{
		pNum[i] = oth[oth.size() - 1 - i] - '0';
	}
	for (int i = rsize; i < pNum.size(); i++)
	{
		pNum[i] = 0;
	}
	return *this;
}

BigInt BigInt::operator+(const BigInt & oth)
{
	if (rsize >= oth.rsize)
	{
		BigInt temp(rsize);
		for (int i = 0; i < oth.rsize; i++)
		{
			temp.pNum[i] = pNum[i] + oth.pNum[i];
		}
		for (int i = oth.rsize; i < rsize; i++)
		{
			temp.pNum[i] = pNum[i];
		}
		for (int i = 0; i < temp.rsize; i++)
		{
			if (temp.pNum[i] > 9)
			{
				temp.pNum[i] = temp.pNum[i] - 10;
				temp.pNum[i + 1]++;
			}
		}
		if (temp.pNum[rsize] != 0)
		{
			temp.rsize++;
		}
		return temp;
	}
	else
	{
		BigInt temp(oth.rsize);
		for (int i = 0; i < rsize; i++)
		{
			temp.pNum[i] = pNum[i] + oth.pNum[i];
		}
		for (int i = rsize; i < oth.rsize; i++)
		{
			temp.pNum[i] = oth.pNum[i];
		}
		for (int i = 0; i < temp.rsize - 1; i++)
		{
			if (temp.pNum[i] > 9)
			{
				temp.pNum[i] = temp.pNum[i] - 10;
				temp.pNum[i + 1]++;
			}
		}
		if (temp.pNum[rsize] != 0)
		{
			temp.rsize++;
		}
		return temp;
	}
}

BigInt BigInt::operator-(const BigInt & oth)
{
	BigInt temp(*this);
	for (int i = 0; i < temp.rsize; i++)
	{
		temp.pNum[i] += 10;
	}
	for (int i = 0; i < oth.rsize; i++)
	{
		temp.pNum[i] -= oth.pNum[i];
	}
	for (int i = 0; i < temp.rsize; i++)
	{
		if (temp.pNum[i] < 10)
		{
			temp.pNum[i + 1]--;
		}
		else
		{
			temp.pNum[i] -= 10;
		}
	}
	return temp;
}

BigInt BigInt::operator*(const BigInt & oth)
{
	BigInt temp(oth.rsize + rsize);
	BigInt oth_temp = oth;
	for (int i = 0; i < rsize; i++)
	{
		for (int j = 0; j < pNum[i]; j++)
		{
			temp = temp + oth_temp;
		}
		oth_temp.mult10(1);
	}
	temp.rsize = temp.realsize();
	return temp;
}

BigInt BigInt::operator/(const BigInt & oth)
{
	BigInt temp(*this);
	BigInt oth_temp = oth;
	BigInt result(rsize - oth.rsize);
	int index_result = temp.rsize - oth_temp.rsize;
	oth_temp.mult10(temp.rsize - oth_temp.rsize);
	while (index_result >= 0)
	{
		while (temp >= oth_temp)
		{
			temp = temp - oth_temp;
			result.pNum[index_result] = result.pNum[index_result] + 1;
		}
		index_result--;
		oth_temp.div10(1);
	}
	result.rsize = result.realsize();
	return result;
}

BigInt BigInt::operator%(const BigInt & oth)
{
	BigInt temp(*this);
	BigInt oth_temp = oth;
	if (temp < oth_temp)
	{
		return temp;
	}
	oth_temp.mult10(temp.rsize - oth_temp.rsize);
	while (oth_temp >= oth)
	{
		while (temp >= oth_temp)
		{
			temp = temp - oth_temp;
		}
		oth_temp.div10(1);
	}
	temp.rsize = temp.realsize();
	return temp;
}

BigInt BigInt::operator+=(const BigInt & oth)
{
	BigInt temp(*this);
	temp = temp + oth;
	return temp;
}

BigInt BigInt::operator-=(const BigInt & oth)
{
	BigInt temp(*this);
	temp = temp - oth;
	return temp;
}

BigInt BigInt::operator*=(const BigInt & oth)
{
	BigInt temp(*this);
	temp = temp * oth;
	return temp;
}

BigInt BigInt::operator/=(const BigInt & oth)
{
	BigInt temp(*this);
	temp = temp / oth;
	return temp;
}

BigInt BigInt::operator%=(const BigInt & oth)
{
	BigInt temp(*this);
	temp = temp % oth;
	return temp;
}
