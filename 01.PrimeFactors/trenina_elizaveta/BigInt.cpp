#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
//#include "BigInt.h"
using namespace std;

class BigInt {
private:
	string s;
	vector< int> _digits;
	bool flag = 0;//is_negative->no
public:

	int get_size()//My
	{
		return _digits.size();
	}

	BigInt(string  str) {
		if (str.length() != 0) {
			if (str[0] == '-') {
				flag = 1;
				s = str.substr(1);//	s=string(str,1,str.length());
			}
			else {
				s = str;
			};
			// _digits.clear();//for(int i=0;i<size;i++) 

			for (unsigned int i = s.length() - 1; i != -1; i--) //long long
			{
				//_digits.push_back(atoi(str.substr(i,1).c_str()));
				_digits.push_back((s[i]) - '0');
			};
			_remove_leading_zeros();
		}

	}
	BigInt(long long a = 0) {
		if (a < 0) {
			flag = 1;
			a = -a;
		}

		do {
			_digits.push_back(a % 10);
			s += a % 10 + '0';
			a = a / 10;
		} while (a != 0);
		int i, j;
		char c;

		for (i = 0, j = s.length() - 1; i < j; i++, j--) { //reverse (s)
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}

	}
	BigInt(const BigInt& bi) {
		flag = bi.flag;
		for (unsigned int i = 0; i < bi._digits.size(); i++)
		{
			_digits.push_back(bi._digits[i]);
		}
	}


	int operator==(const BigInt &bi) const;
	int operator < (const BigInt &bi) const;
	int operator !=(const BigInt& bi) const;
	int operator <=(const BigInt& bi)const;
	int operator >(const BigInt& bi) const;
	int operator >=(const BigInt& bi) const;

	BigInt& operator=(const BigInt& bi);
	friend const BigInt  operator +(const BigInt & left, const BigInt& right);
	friend const BigInt operator -(const BigInt& left, const BigInt& right);
	friend const BigInt operator *(const BigInt& left, const BigInt& right);
	friend const BigInt operator /(const BigInt& left, const BigInt& right);
	friend const BigInt operator %(const BigInt& left, const BigInt& right);
	friend const BigInt operator ^(const BigInt& left, int right);
	friend const BigInt  operator +(const BigInt & left, int right);
	friend const BigInt operator -(const BigInt& left, int right);
	friend const BigInt operator *(const BigInt& left, int right);
	friend const BigInt operator %(const BigInt& left, int right);
	friend const BigInt operator /(const BigInt& left, int right);
	friend int operator ==(const BigInt& left, int right);


	friend BigInt&  operator ++(/*const*/ BigInt & k, int);

	friend ostream& operator <<(ostream& os, const BigInt& bi);
	//friend istream& operator >>(istream& is, const BigInt& bi);
	//friend istream& operator >>(istream& is, const string& s);
	BigInt operator-() const;
	void _remove_leading_zeros();
	void _shift_right();
	BigInt& operator=(/*const*/ int i);
};

void BigInt::_shift_right() {
	/*if (_digits.size() == 0) {
		_digits.push_back(0);
		return;
	}*/
	_digits.insert(_digits.begin(), 0);
}
void BigInt::_remove_leading_zeros() {
		while (_digits.size() > 1 && _digits.back() == 0) {
			_digits.pop_back();
		}
		// ýòîò êîä íóæåí, ÷òîáû ó íàñ íå áûëî îòðèöàòåëüíîãî íóëÿ
		if (_digits.size() == 1 && _digits[0] == 0) flag = false;
	}
ostream& operator <<(ostream& os, const BigInt& bi) {
	
	if (bi.flag) {
		os << '-';
	}
	for (int i = bi._digits.size(); i > 0; i--)//
	{
		os << bi._digits[i-1];
	}
	
	//os << bi.s;
	return os;
}
istream& operator >>(istream& is, BigInt& bi) {
	//int i = 0;
	string c;
	is >> c;
	bi = BigInt(c);
	return is;
}


int BigInt:: operator==(const BigInt &bi) const {
	if (bi.flag != flag) return 0;
	if (_digits.empty()) { //2 ïðåäñòàâëåíèÿ 0
		if ((bi._digits.empty()) || ((bi._digits[0] == 0) && (bi._digits.size() == 1))) return 1;
		else return 0;
	}
	if (bi._digits.empty()) {
		if (_digits.empty() || (_digits[0] == 0) && (_digits.size() == 1)) return 1;
		else return 0;
	}
	if (_digits.size() == bi._digits.size()) {
		for (unsigned int i = 0; i < _digits.size(); i++) 
			if (_digits[i] != bi._digits[i]) return 0; return 1;
	}
	return 0;

}
int BigInt:: operator < (const BigInt &bi) const //a<b
{
	if (*this == bi) return 0;
	if (flag) {
		if (bi.flag) return ((-bi) < (-*this));
		else return 1; 
	}
	if (bi.flag) return 0;
	
		if (_digits.size() != bi._digits.size()) {
			return _digits.size() < bi._digits.size();
		}
		else {
			for (long long i = _digits.size() - 1; i >= 0; /*--i*/i--) {
				if (_digits[i] != bi._digits[i]) return _digits[i] < bi._digits[i];
			}
			return 0;
		}	
}
 BigInt BigInt:: operator-() const {
	BigInt copy(*this);
	copy.flag = !copy.flag;
	return copy;
}
 int BigInt:: operator !=(const BigInt& bi) const {
	 return !(*this == bi);
 }
 int BigInt:: operator <=(const BigInt& bi)const {
	 return (*this < bi || *this == bi);
 }
 int BigInt:: operator >(const BigInt& bi) const {
	 return !(*this <= bi);
 }
 int BigInt:: operator >=(const BigInt& bi) const {
	 return !(*this < bi);
 }
 BigInt& BigInt:: operator=(const BigInt& bi)
 {
	 if (&bi != this)
	 {
		 flag = bi.flag;
		 _digits = bi._digits;//clear?
	 }
	 return *this;
 }

 BigInt& BigInt:: operator=( int i)
 {	 
	 return *this = BigInt(i);
 }

 const BigInt   operator +( const BigInt & left, const BigInt& right) { //a+b  a>b
	 if (left.flag) {
		 if (right.flag) return -(-left + (-right));
		 else return right - (-left);
	 }
	 else if (right.flag) return left - (-right);

	 if (left < right) return right + left;
	 int carry = 0; // ôëàã ïåðåíîñà èç ïðåäûäóùåãî ðàçðÿäà
	 int i = 0, t = 0;
	 
	 BigInt res(left)/*, a(left)*/;

	 res._digits.push_back(0);
	 while (i < right._digits.size()) {
		 t = res._digits[i] + right._digits[i] + carry;
		 res._digits[i++] = t % 10;
		 carry = t / 10;
	 }
	 while ((i < res._digits.size()) && (carry != 0))
	 {
		 t = res._digits[i] + carry;
		 res._digits[i++] = t % 10;
		 carry = t / 10;
	 }

	 res._remove_leading_zeros();
	 return res;
 }
 const BigInt operator -(const BigInt& left, const BigInt& right) {
	 if (right.flag) { return left + (-right); }
	 if (left.flag) { return -(-left + right); }
	 if (left < right) { return -(right - left); } //a>b  a-b
	 
	 BigInt res(0); 
	 res._digits.clear();
	 /*for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
		 left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
		 carry = left._digits[i] < 0;
		 if (carry != 0) left._digits[i];
	 };*/
		 int carry = 0;  
		 int i = 0;
		 while (i < right._digits.size()) {
			if (left._digits[i] - carry < right._digits[i])
			 {
				 res._digits.push_back(10 + left._digits[i] - right._digits[i] - carry);
				 carry =  1;
			 }
			 else {
				res._digits.push_back(left._digits[i] - right._digits[i] - carry);
				carry = 0;
			 }
			i++;
		 }
		 for ( i; i <  left._digits.size(); i++)  
		 {	
			 if (left._digits[i] < carry )
			 {
				 res._digits.push_back(10 + left._digits[i] - carry);
				 carry = 1;
			 }
			 else {
				 res._digits.push_back(left._digits[i] - carry);
				 carry = 0;
			 }		 
		 }
	  res._remove_leading_zeros();
	  return res;

 }
 const BigInt operator *(const BigInt& left, const BigInt& right) {
	 if (left.flag) {
		 if (right.flag) return (-left)*(-right);
		 else return -((-left)*right);
	 }
	 else if (right.flag) return -(left*(-right));   
	 if (left < right) return right * left;// a>b (a>=b)
	 if ((left._digits.size() == 0) || ((left._digits.size() == 1) && (left._digits[0] == 0))) return BigInt(0);//ïðîâåðêà íà íîëü äîáàâèòü
	 int carry = 0;
	 BigInt res("0"); res._digits.resize(left._digits.size() + right._digits.size() + 1, 0);
	 //res._digits.clear();
	 
	 for (int i = 0; i < left._digits.size(); i++) 
	 {
		 for (int j = 0; j < right._digits.size(); j++)
		 {
			 res._digits[i + j] += right._digits[j] * left._digits[i];	
		 }
	 }
	 for (int i = 0; i < res._digits.size()-1; i++)
	 {
		 res._digits[i + 1] += res._digits[i] / 10;
		 res._digits[i] %= 10;
	 }

	 res._remove_leading_zeros();
	 return res;
 }
 const BigInt operator /(const BigInt& left, const BigInt& right) //a/b
 {
	 if (left.flag)
	 {
		 if (right.flag) return (-left) / (-right);
		 return -((-left) / right);
	 }
	 if (right.flag) return -(left / (-right));
	 if (right > left) return BigInt("0");
	 if ((right._digits.size()==0)|| ((right._digits.size()==1)&&(right._digits[0]==0))) return BigInt(-1);

	
	 BigInt b (right);
	 BigInt result, current;
	 result._digits.resize(left._digits.size());
	 for (long long i = left._digits.size() - 1; i >= 0; --i) {
		 current._shift_right();
		 current._digits[0] = left._digits[i];
		 current._remove_leading_zeros();
		 int x = 0, l = 0, r = 10;//base=10?
		 while (l <= r) {
			 int m = (l + r) / 2;
			 BigInt t = b * m;
			 if (t <= current) {
				 x = m;
				 l = m + 1;
			 }
			 else r = m - 1;
		 }

		 result._digits[i] = x;
		 current = current - b * x;
	 }
	// result._is_negative = left._is_negative != right._is_negative;
	 result._remove_leading_zeros();
	 if (result._digits.size() == 0) result._digits.push_back(0);
	 return result;	 	 	  
 }
 const BigInt operator %(const BigInt& left, const BigInt& right)
 {
	 BigInt res = left - (left / right)*right;
	 res._remove_leading_zeros();
	 if (res._digits.size() == 0) res._digits.push_back(0);
	 return res;
 }
 

 int operator ==(const BigInt& left, int right) {
	 return left == BigInt(right);
 }
 BigInt&  operator ++( BigInt & k, int) {
	 k= k + BigInt(1);
	 return k;
 }
 const BigInt  operator +(const BigInt & left, int right) {
	 return left + BigInt(right);
 }
 const BigInt operator -(const BigInt& left, int right) {
	 return left - BigInt(right);
 }
 const BigInt operator *(const BigInt& left, int right) {
	 return left * BigInt(right);
 }
 const BigInt operator %(const BigInt& left, int right) { 
	 return left % BigInt(right); }
 const BigInt operator /(const BigInt& left, int right) { 
	 return left / BigInt(right); }
 const BigInt operator ^(const BigInt& left, int right)
 {
	 if (right == 0) return BigInt(1);
	 if (right > 0) { 		 
		 BigInt res(left);
		 for (int i = 1; i < right; i++)
		 {
			 res = res * left;
		 }
		 return res;
	 }
	 else {
		 return BigInt(-1);
	 }

 }

 /*template <typename T>
 double factor(T a) {

	 T  k, j1, j2;
	 double flag = 1;//prime

	 chrono::time_point<chrono::high_resolution_clock> start, stop;
	 start = std::chrono::high_resolution_clock::now();

	 k = 1; j1 = k * 6 - 1; j2 = k * 6 + 1;
	 if (a % 2 == 0) {
		 flag = -1;//nonprime
		 a = a / 2;
	 }
	 if (a % 3 == 0) {
		 flag = -1;//nonprime
		 a = a / 3;
	 }

	 while (j2*j2 <= a)
	 {
		 if (a%j1 == 0) {
			 flag = -1;//nonprime
			 a = a / j1;
		 }
		 if (a%j2 == 0) {
			 flag = -1;//nonprime
			 a = a / j2;
		 }
		 k++;
		 j1 = k * 6 - 1;
		 j2 = k * 6 + 1;
	 }


	 stop = std::chrono::high_resolution_clock::now();
	 return flag * std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

 }*/

 
 /*double*/ int factor(BigInt & bi) {

	 BigInt  k, j1, j2, a(bi);
	 int /*double*/ flag = 1;//prime

	/* chrono::time_point<chrono::high_resolution_clock> start, stop;
	 start = std::chrono::high_resolution_clock::now();*/

	 //_start:
	 k = 1; j1 = k * 6 - 1; j2 = k * 6 + 1;
	 while ((a % 2) == 0) {
		 flag = -1;//nonprime
		 a = a / 2;
	 }
	 while (a % 3 == 0) {
		 flag = -1;//nonprime
		 a = a / 3;
	 }

	 while (j2*j2 <= a)
	 {
		 while (a%j1 == 0) {
			 flag = -1;//nonprime
			 a = a / j1;
			 //return factor(a);
			 //goto _start;
		 }
		 while (a%j2 == 0) {
			 flag = -1;//nonprime+6
			 a = a / j2;
			 //return factor(a);
			// goto _start;
		 }
		 k++;
		 j1 = k * 6 - 1;
		 j2 = k * 6 + 1;
		 if ((j2 < 150) && (j2 > 130)) cout << j2 << endl;
		 if ((j2 < 6936) && (j2 > 6000)) cout << j2 << endl;
		 if ((j2 < 10010) && (j2 > 10000)) cout << j2 << endl;
		 if ((j2 < 30200) && (j2 > 30000)) cout << j2 << endl;
		 if ((j2 < 60000) && (j2 > 59898)) cout << j2 << endl;
		 if ((j2 < 693635) && (j2 > 600000)) cout << j2 << endl;
		 if ((j2 < 69363506) && (j2 > 60000000)) cout << j2 << endl;
		 if ((j2 < 6936350613) && (j2 > 6000000000)) cout<<j2<<endl;

	 }

	 return flag;
	 /*stop = std::chrono::high_resolution_clock::now();
	 return flag * std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();*/

 }

 double time_factor(BigInt & a) {
	 chrono::time_point<chrono::high_resolution_clock> start, stop;
	 start = std::chrono::high_resolution_clock::now();

	 /*double*/ int flag = factor(a);
	 stop = std::chrono::high_resolution_clock::now();
	 return flag * (std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
 }

 BigInt operator_a_plus_b_modN(BigInt a, BigInt b, BigInt N)
 {
	 BigInt t = a + b;
	 if (t >= N) t = t - N;
	 return t;
 }
 BigInt operator_a_multiply_b_modN(BigInt a, BigInt b, BigInt N)
 {
	 BigInt t = a * b;
	 t = t % N;
	 return t;
 }

 BigInt operator_x_exponentiation_y_modN(BigInt x, BigInt y, BigInt N)
 {
	 BigInt d("2");
	 if (y == 0) return BigInt("1");
	 BigInt z = operator_x_exponentiation_y_modN(x,y/2,N);

	 if (y % d == 0) return operator_x_exponentiation_y_modN(z, d, N);
	 else return  operator_a_multiply_b_modN(x,operator_x_exponentiation_y_modN(z, d, N),N);
 }

 int main()
 {

	// {
 //    string st1 = "-1234567";
	// string st2 = "1234567";
	// BigInt a(st1); BigInt b(-12345);
	// //cout << st1.length(); //8
	// //cout << st2.length()<<endl;//7
	// ////cout << "st1= st2= length \n";
	// //cout << "a.size =" << a.get_size();
	// cout << "a=" << a << endl;
	// cout << "b=" << b << endl;
	// cout << "a*b =" << b * a << endl;
	// BigInt res(a*b);
	// BigInt div(res / a), di(res%a), d("123546898654");   d = d % a;
	// cout << "res/a=b =" << div << endl;
	// cout << "res%a= " << d << endl;
 //}
	// BigInt a("17"); int b = 3;
	// cout << "a^b=" << operator^(a, b);

	 /*typedef  BigInt Type;
	 Type a;
	 Type mas[100];
	 double time[100];*/



	 //BigInt b("123456789");
	 //BigInt b("48112959837082048787");//ïðîñòîå
	 //BigInt b("122296951006737507");
	 ///*double*/ int res = factor(b);
	 //cout << "res=" << res << endl;
	 //double otvet = time_factor(b);
	 //cout << "otvet=" << time_factor(b) << "  " << otvet;

	 BigInt a("93200"), b("234"), N("1000"), t("3");

	 BigInt res = operator_a_multiply_b_modN(a,b,N);
	 BigInt  r = operator_x_exponentiation_y_modN(a,/*BigInt("3")*/ t,N);
	 cout << "res=" << res<<endl;
	 


	 //cout << "h\n";     //operator+
	 //BigInt a(1999), b(49), c(9991), d(94), e(999), f(99999);
	 //cout << a + b << "  " << b + a<<endl;   //2048  
	 //cout << c + d << "  " << d + c << endl;  //10085
	 //cout << e + f << " " << f + e << endl; //100998


	 {
		 //ifstream file("primes20.in.txt");
		 //if (file.is_open()) {
			// int i = 0;
			// while (!file.eof() && (i < 100))
			// {
			//	 file >> a;
			//	 mas[i++] = a;
			// }
			// file.close();

			// cout << "file is open";
		 //};

		 //for (int i = 0; i < 100; i++)
		 //{
			// time[i] = factor(mas[i]);
		 //};

		 //ofstream fout("primes20.out.trenina.txt");// ñîçäà¸ì îáúåêò äëÿ çàïèñè â ôàéë
		 //for (int i = 0; i < 100; i++)
		 //{
			// fout << time[i] << endl;
		 //}

		 //fout.close();
	 }//file

	system("pause");
	return 0;
}
