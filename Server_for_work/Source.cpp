#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include <windows.h>
#include <mutex>

using namespace std;
int n = 6, i = 0, sum = 0;				//64 символа на ввод
string ss;
string intStr;
mutex mtx;

int foo_str_to_int(string s)
{
	string s = "74 319 432 82 95 0 1";
	vector<int> v;

	auto ptr = s.c_str();
	char* endptr = nullptr;
	while (ptr != s.c_str() + s.size()) {
		auto value = strtol(ptr, &endptr, 10);
		if (ptr == endptr) {
			ptr++;
		}
		else {
			ptr = endptr;
			v.push_back(value);
		}
	}

	copy(begin(v), end(v), ostream_iterator<int>(cout, " "));

	for (auto now : v)
	{
		return now;
	}
}
string first()
{	
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

	
	lock_guard<mutex> guard(mtx);
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
	return intStr;	
}

//2 программа
int second(string intStr)
{
	lock_guard<mutex> guard(mtx);
	int i = 0;
	//Придумать, как переводить из строки в массив int
	cout << "\nМассив символов:\n" << intStr;
	for (size_t k = intStr.find('К'); k != intStr.npos; k = intStr.find('К', k))
	{
		intStr.erase(k, 3);
		i++;
	}
	cout << "\nМассив изменённых символов:\n" << intStr << endl << flush;

	//на этом месте будет неоднозначный вызов, потому что нужно из функции как-то вернуть массив
	foo_str_to_int(intStr);
	return 0;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	thread t1(first);
	t1.join();
	thread t2(second, intStr);
	t2.join();
	return 0;
	}

	//Реализовать потоки. Один вечно считывает данные, другой вечно печатает. Синхронизировать
	//считать интовый массив, потом собрать массив строк и потом в массив

	//копировать инты из стринга в массив интовый и с ним уже работать
