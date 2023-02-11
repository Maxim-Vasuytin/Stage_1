#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "\t\t....FILEMAPPING CLIENT or CHILD...." << endl;
	cout << endl;

	//local Varible Deinition

	HANDLE hFileMap;
	BOOL bResult;
	PCHAR lpBuffer = NULL;

	//step-1 OpenFileMapping
	hFileMap = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		L"Local\\MyFileMap");
	if (hFileMap == FALSE)
	{
		cout << "OpenFileMapping Faild & Error № " << GetLastError() << endl;
	}
	cout << "OpenFileMapping Success" << endl;

	//step-2 MapViewOffFile
	lpBuffer = (PCHAR)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256);
	if (lpBuffer == NULL)
	{
		cout << "MapViewOffFile Faild & Error № " << GetLastError() << endl;
	}
	cout << "MapViewOffFile Success" << endl;

	//step-3 Reading the Data from File-Ma Object
	cout << "DATA READING FROM SERVER or  PARRENT PROCESS: " << lpBuffer << endl;
	
	int local_buff = atoi(lpBuffer);

	//step-4 UnmapViewOfFile
	bResult = UnmapViewOfFile(lpBuffer);
	if (lpBuffer == NULL)
	{
		cout << "Unmapping Error = " << GetLastError() << endl;
	}
	cout << "Unmapping Success" << endl;

	//step-5 Close Handle
	CloseHandle(hFileMap);


	system("pause");
	cout << "Нажмите любую клавишу, чтобы очистить...";
	system("cls");


	if ((local_buff % 32 == 0) && (sizeof(local_buff) > 2))
	{
		cout << "\tДанные получены!\tРезультат = " << local_buff << endl;
	}
	else cout << "\tОшибка!\tПерепроверьте введённые данные";
	system("pause");

	return 0;
}