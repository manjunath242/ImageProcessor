//#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <iostream>

void NetworkSetup();

int main()
{

	NetworkSetup();
	
	return 0;
}

void NetworkSetup()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//local broadcast
	addr.sin_port = htons(1111);//port
	addr.sin_family = AF_INET;//IPV4 socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);//create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Address bind in socket
	listen(sListen, SOMAXCONN);// puts in a state to lsiten for incoming

	SOCKET newConnection;//Socket to hold client's connection
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen);//Accept new connection

	if (newConnection == 0)
	{
		std::cout << "Failed to accept client " << std::endl;
	}

	else
	{
		std::cout << "accepted client " << std::endl;
		//WSACleanup();
		char lane[256] = "1";

		while (true)
		{
			send(newConnection, lane, sizeof(lane), NULL);
		}

	}

	system("pause");
}