#pragma comment(lib, "ws2_32.lib")
#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include <windows.h>
#include <mutex>

#pragma warning(disable: 4996)

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


	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); 
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;		
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET; 
	int sizeofaddr = sizeof(addr);

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	connect(Connection, (SOCKADDR*)&addr, sizeofaddr);

	const char tosend = htons(sum);
	int size = sizeof(sum);

	send(Connection, &tosend, size, 0);

	system("pause");
	
	return 0;
	}
