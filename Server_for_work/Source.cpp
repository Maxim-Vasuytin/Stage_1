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

	cout << "\nОбработанный вектор:\n";
	copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
	
	for (auto now : v)
	{
		sum += now;
	}

	return sum;
	//Возвращаю вектор интов, который готов к отправке на сервер
}

//Первая программа
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

	//Удаление лишних символов
	cout << "\nМассив символов:\n" << intStr << endl;
	for (size_t k = intStr.find('К'); k != intStr.npos; k = intStr.find('К', k))
	{
		intStr.erase(k, 3);
		i++;
	}
	//cout << "\nМассив изменённых символов:\n" << intStr << endl << flush;

	sum = foo_str_to_int(intStr);
	cout << "\n\nСумма массива нечётных чисел = " << sum << endl << endl;
	
	return sum;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	thread t1(first);
	t1.join();
	thread t2(second, intStr);		
	t2.join();


	cout << "\t\t....FILEMAPPING SERVER or PARENT...." << endl;
	cout << endl;

	
	HANDLE hFileMap;
	BOOL bResult;
	PCHAR lpBuffer = NULL;
	char Buffer[1024];
	_itoa_s(sum, Buffer, 10);
	size_t szBuffer = sizeof(Buffer);


	//CreateFileMapping
	hFileMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		256,
		L"Local\\MyFileMap");
	if (hFileMap == FALSE)
	{
		cout << "CreateFileMapping Faild & Error № " << GetLastError() << endl;
	}
	cout << "CreateFileMapping Success" << endl;

	//step-2 MapViewofffile
	lpBuffer = (PCHAR)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256
	);
	if (lpBuffer == NULL)
	{
		cout << "MapViewOffFile Faild & Error № " << GetLastError() << endl;
	}
	cout << "MapViewOffFile Success" << endl;

	//step-3 CopyMemory
	CopyMemory(lpBuffer, Buffer, szBuffer);


	//step-4 UnmapViewOffFile
	bResult = UnmapViewOfFile(lpBuffer);
	if (bResult == FALSE)
	{
		cout << "UnMapViewOffFile Faild & Error № " << GetLastError() << endl;
	}
	cout << "UnMapViewOffFile Success" << endl;

	
	cout << "\n\n\tНажмите любую клавишу, чтобы очистить...";
	system("pause");
	system("cls");
	system("pause");
	
	return 0;
	}


	//Реализовать клиент-серверное приложение 
