#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

void main()
{
	setlocale(LC_ALL, "rus");
	int n = 3, i = 0, sum = 0;				//64 символа на ввод
	vector <int> data(n);
	string ss;
	string intStr;


	//Проверить принадлежность символа к числовым значениям

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
	for (int i = 0; i<n;i++)
	{
		stringstream ss;
		if (data[i]%2 == 0)
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


	//2 программа
	cout << "\n\nСумма обработанного массива = " << sum << endl << flush;

	//Реализовать потоки. Один вечно считывает данные, другой вечно печатает. Синхронизировать
	//считать интовый массив, потом собрать массив строк и потом в массив

	//копировать инты из стринга в массив интовый и с ним уже работать
}