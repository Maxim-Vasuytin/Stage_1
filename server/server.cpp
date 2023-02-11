#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <Windows.h>
#include <iostream>

#pragma warning(disable: 4996)
using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection)
	{
		char result = { '\0' };
		int size = sizeof(result);
		recv(newConnection, &result, size, 0);
		const char recv_buffer = ntohs(result);

		cout << "\tДанные получены!\tРезультат = " << recv_buffer << "\t" << &result << endl;
	}
	/*if (((int)recv_buffer % 32 == 0) && (sizeof((int)recv_buffer) > 2))
	{
		cout << "\tДанные получены!\tРезультат = " << (int)recv_buffer << endl;
	}
	else cout << "\tОшибка!\tПерепроверьте введённые данные";*/
	system("pause");

	return 0;
}