#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <fstream>
#include "BigIntegerLibrary.hh"

using namespace std;

class ModInt {
private:
	BigInteger value, mod;
public:
	ModInt(BigInteger &_x, BigInteger &_mod) : value(_x), mod(_mod) {}
	ModInt(const ModInt &modint) : value(modint.value) , mod(modint.mod) {}
	BigInteger operator+(const BigInteger &b) const;
	BigInteger operator-(const BigInteger &b) const;
};

BigInteger ModInt::operator+(const BigInteger &b) const {
	return 0;
}

BigInteger ModInt::operator-(const BigInteger &b) const {
	return 0;
}

int isPrime(BigInteger x) {
	if (x == 2) return 1;
	for (BigInteger i = 2; i*i < x; i++) {
		if (x % i == 0)
			return 0;
	}
	return 1;
}

void prime_divisors(BigInteger numb) {
	BigInteger divisor = 2;
	while (divisor*divisor <= numb)
	{
		if (numb%divisor == 0)
		{
			cout << divisor;
			numb = numb / divisor;
			cout << " ";
		}
		else if (divisor == 2) divisor = 3;
		else divisor = divisor + 2;
	}
	cout << numb;
}


int main() {
	std::string s;
	//ifstream fin("in_primeFactors\\random20_in.txt");
	//ofstream fout("out_primeFactors\\random20_out.txt");
	BigInteger x;
	int start = clock();
	s = "11967867867890780";
	x = stringToBigInteger(s);
	prime_divisors(x);
	int end = clock();
	cout << endl;
	int time = (end - start);
	cout << time << endl;

	

	system("pause");
}
