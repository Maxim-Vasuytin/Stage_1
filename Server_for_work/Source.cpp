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
	int n = 3, i = 0, sum = 0;				//64 ������� �� ����
	vector <int> data(n);
	string ss;
	string intStr;


	//��������� �������������� ������� � �������� ���������

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
	for (int i = 0; i<n;i++)
	{
		stringstream ss;
		if (data[i]%2 == 0)
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


	//2 ���������
	cout << "\n\n����� ������������� ������� = " << sum << endl << flush;

	//����������� ������. ���� ����� ��������� ������, ������ ����� ��������. ����������������
	//������� ������� ������, ����� ������� ������ ����� � ����� � ������

	//���������� ���� �� ������� � ������ ������� � � ��� ��� ��������
}