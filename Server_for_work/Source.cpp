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
int n = 6, i = 0, sum = 0;				//64 ������� �� ����
string ss;
string intStr;
mutex mtx;

vector<int> foo_str_to_int(string s)
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

	cout << "\n������������ ������:\n";
	copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
	
	return v;
	//��������� ������ �����, ������� ����� � �������� �� ������
}

//������ ���������
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
	//���������� �� ��������
	sort(begin(data), end(data), greater<>());

	//��������� ������ �����
	for (int i = 0; i < n; i++)
	{
		stringstream ss;
		if (data[i] % 2 == 0)
		{
			intStr += "�� ";
		}
		else
		{
			ss << data[i];
			intStr += ss.str() + " ";
		}
	}	
	return intStr;	
}

//2 ���������
int second(string intStr)
{
	lock_guard<mutex> guard(mtx);
	int i = 0;	

	//�������� ������ ��������
	cout << "\n������ ��������:\n" << intStr;
	for (size_t k = intStr.find('�'); k != intStr.npos; k = intStr.find('�', k))
	{
		intStr.erase(k, 3);
		i++;
	}
	cout << "\n������ ��������� ��������:\n" << intStr << endl << flush;

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


	//����� ����� �������
	//����������� ������-��������� ���������� (���� �������������� ������, ������� ����� ��������� �� ������)
