#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include <windows.h>

using namespace std;
int n = 3, i = 0, sum = 0;				//64 ������� �� ����
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
	cout << "\n������ ��������:\n" << intStr;
	return intStr;
}

//2 ���������
int second(string intStr)
{
	//���������, ��� ���������� �� ������ � ������ int
	cout << "\n\n����� ������������� ������� = " << sum << endl << flush;
	return 0;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	thread t1(first);
	t1.join();
	cout << "\n����������:\t" << intStr;
	thread t2(second, intStr);
	t2.join();
	return 0;
	}

	//����������� ������. ���� ����� ��������� ������, ������ ����� ��������. ����������������
	//������� ������� ������, ����� ������� ������ ����� � ����� � ������

	//���������� ���� �� ������� � ������ ������� � � ��� ��� ��������
