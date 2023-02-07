#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include <windows.h>

using namespace std;
int n = 3, i = 0, sum = 0;				//64 символа на ввод
string ss;
string intStr;

string first()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector <int> data(n);
	setlocale(LC_ALL, "rus");
	cout << "Enter only numeric values: " << flush << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> data[i];
		if (cin.fail())
		{
			cin.clear();
			cout << "Mistake. Enter only numbers!" << endl;
			break;
		}
	}
	//Сортировка по убыванию
	sort(begin(data), end(data), greater<>());

	//Изменение чётных чисел
	for (int i = 0; i < n; i++)
	{
		stringstream ss;
		if (data[i] % 2 == 0)
		{
			intStr += "КВ ";
		}
		else
		{
			ss << data[i];
			intStr += ss.str() + " ";
		}
	}
	cout << "\nМассив символов:\n" << intStr;
	return intStr;
}

//2 программа
int second(string intStr)
{
	//Придумать, как переводить из строки в массив int
	cout << "\n\nСумма обработанного массива = " << sum << endl << flush;
	return 0;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	thread t1(first);
	t1.join();
	cout << "\nаХХХАХАХХА:\t" << intStr;
	thread t2(second, intStr);
	t2.join();
	return 0;
	}

	//Реализовать потоки. Один вечно считывает данные, другой вечно печатает. Синхронизировать
	//считать интовый массив, потом собрать массив строк и потом в массив

	//копировать инты из стринга в массив интовый и с ним уже работать
