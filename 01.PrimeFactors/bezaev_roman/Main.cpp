#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "BigIntegerLibrary.hh"

using namespace std;
// Modulo methods
template <class T>
T Sum(T &a, T &b, T &mod);
template <class T>
T Sub(T &a, T &b, T &mod);
template <class T>
T Mul(T &a, T &b, T &mod);
template <class T>
T Inverse(T &a, T &mod);
template <class T> 
T Pow(T a, T n, T m);

template <class T>
T mul_inv(T a, T b);

// Prime methods
template <class T>
void prime_divisors(T numb);
template <class T>
bool isPrime_simple(T x);

template <class T>
bool ferma(T x);


int main() {
	ifstream fin("in_primeFactors\\prime9_in.txt");
	ofstream fout("out_primeFactors\\prime9_out.txt");

	string s = "12312312312";
	BigInteger a = stringToBigInteger(s);
	cout << ferma(a) << endl;
	system("pause");
}

template <class T> // сложнение по модулю
T Sum(T &a, T &b, T &mod) {
	return (a + b) % mod;
}

template <class T> // вычитание по модулю
T Sub(T &a, T &b, T &mod) {
	if (a >= b) {
		return (a - b) % mod;
	}
	else {
		return a - b + mod;
	}
}

template <class T> // умножение по модулю
T Mul(T &a, T &b, T &mod) {
	return (a * b) % mod;
}

template <class T> // быстрое возведение в степень по модулю
T Pow(T a, int n, T m) {
	T r = 1;
	while (n) {
		if (n % 2 == 1)
			r = Mul(r, a, m);
		a = Mul(a, a, m);
		n /= 2;
	}
	return r;
}

template <class T> // поиск обратного по модулю
T Inverse(T &a, T &mod) {
	if (!(mod%a))
		throw (string)"This number don't have inverse";
	a = a % mod;
	for (int x = 1; x < mod; x++)
		if ((a * x) % mod == 1)
			return x;
}



template <class T> // пробный поиск обратного из интернета
T mul_inv(T a, T b)
{
	T b0 = b, t, q;
	T x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

const int k = 100;
template <class T>
bool ferma(T x) {
	if (x == 2)
		return true;
	srand(time(NULL));
	for (int i = 0; i < k; i++) {
		T rand(rand());
		T a = (rand % (x - 2)) + 2;
		if (gcd(a, x) != 1)
			return false;
		if (Pow(a, x - 1, x) != 1)
			return false;
	}
	return true;
}

template <class T>
T gcd(T a, T b) {
	if (b == 0)
		return a;
	return gcd(b, a%b);
}

template <class T> // простая проверка числа на простоту
bool isPrime_simple(T x) {
	if (x == 2) return 1;
	T i = 2;
	while (i*i <= x) {
		if (x % i == 0)
			return false;
		i += 2;
		if (i % 100000 == 0) {
			cout << i << endl;
		}
	}
	return true;
}

template <class T> // простое разложение числа на множители
void prime_divisors(T numb) {
	T divisor = 2;
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