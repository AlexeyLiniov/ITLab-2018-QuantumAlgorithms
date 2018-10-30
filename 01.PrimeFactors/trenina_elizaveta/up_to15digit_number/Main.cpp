#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

template <typename T> 
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
	 
}

int main()
{
	typedef  int Type;
	Type a;
	Type mas[100];
	double time[100];
		
	
	ifstream file("random9.in.txt");
	if (file.is_open()) {
		int i = 0;
		while (!file.eof()&&(i<100))
		{
			file >> a;
			mas[i++] = a;
		}
		file.close();
	};

 
	for (int i = 0; i < 100; i++)
	{
		time[i] = factor(mas[i]);
	};

	
	ofstream fout("random9.out.trenina.txt");// создаём объект для записи в файл
	for (int i = 0; i < 100; i++)
	{
		fout << time[i] << endl;
	}

	fout.close();
	//system("pause");
	return 0;

}
