#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>


char Buffer[512];
int iResult;
int servlen;
char msg[256] = "Message";
SOCKADDR_IN conService;

DWORD WINAPI ReadingThread(LPVOID param)
{
	SOCKET s = (SOCKET)param;

	do
	{
		iResult = recv(s, Buffer, 512, 0);
		if (iResult <= 0) break;
		Buffer[iResult] = '\0';
		std::cout << "Recv: "  << std::endl;
	} while (true);

	return 0;
}

int main1()
{
	int userType;
	HANDLE hThread;
	DWORD dwThreadID;

	//initialize winsock and create a socket
	WSAData wsaData; // initialize
	iResult = WSAStartup(MAKEWORD(2, 1), &wsaData);

	if (iResult != NO_ERROR) // check for errors
	{
		std::cout << "Error at WSAStartup()" << std::endl;
		return 0;
	}

	std::cout << "WSAStartup() is OK." << std::endl;

	// Ask the user if he is server or client
	std::cout << "Hi, which type of user are you? 1 - Server, 2 - Client" << std::endl;
	std::cin >> userType;

	SOCKET sockSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// depending on the declared user type, execute the appropriate code
	if (userType == 1)
	{
		// create socket
		 // create a socket
		if (sockSocket == INVALID_SOCKET) // check for errors
		{
			std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
			WSACleanup();
			return 0;
		}

		std::cout << "Socket() is OK." << std::endl;

		SOCKADDR_IN service;
		// bind to socket
		service.sin_addr.s_addr = INADDR_ANY;
		service.sin_family = AF_INET;
		service.sin_port = htons(2222);

		if (bind(sockSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) // cheking for errors
		{
			std::cout << "Error at bind(): " << WSAGetLastError() << std::endl;
			closesocket(sockSocket);
			WSACleanup();
			return 0;
		}

		std::cout << "Bind() is OK." << std::endl;

		// listen
		if (listen(sockSocket, 10) == SOCKET_ERROR) // check for errors
		{
			std::cout << "Error at listen(): " << WSAGetLastError() << std::endl;
			closesocket(sockSocket);
			WSACleanup();
			return 0;
		}

		std::cout << "Listen() is OK." << std::endl;

		//accept connection
		servlen = sizeof(service);
		std::cout << "Waiting for user to connect..." << std::endl;

		SOCKET acceptSocket = accept(sockSocket, (SOCKADDR*)&service, &servlen);
		//if (acceptSocket != INVALID_SOCKET)
		//{
		//	std::cout << "Error at accept(): " << WSAGetLastError() << std::endl;
		//	closesocket(sockSocket);
		//	WSACleanup();
		//	return 0;
		//}

		std::cout << "A client has connected" << std::endl << std::endl;

		// receive messages
		//hThread = CreateThread(NULL, 0, &ReadingThread, (void*)acceptSocket, 0, &dwThreadID);
		//if (!hThread)
		//{
		//	std::cout << "Error at CreateThread(): " << GetLastError() << std::endl;
		//	closesocket(acceptSocket);
		//	closesocket(sockSocket);
		//	WSACleanup();
		//	return 0;
		//}

		// send messages

		

		//do
		//{
			//std::string message;
			//if (!std::getline(std::cin, message))
			//	break;

			if (send(acceptSocket, "1", sizeof(msg), 0) == SOCKET_ERROR)
			{
				std::cout << "Error at send(): " << WSAGetLastError() << std::endl;
				//break;
			}

			//if (GetAsyncKeyState(VK_ESCAPE))
			//{
			//	closesocket(acceptSocket);

			//	//WaitForSingleObject(hThread, INFINITE);
			//	//CloseHandle(hThread);

			//	closesocket(sockSocket);
			//	WSACleanup();
			//	return 0;
			//}

		//} while (true);


	}

	//else if (userType == 2)
	//{
	//	// create socket
	//	sockSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // create a socket
	//	if (sockSocket == INVALID_SOCKET) // check for errors
	//	{
	//		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
	//		WSACleanup();
	//		return 0;
	//	}

	//	std::cout << "Socket() is OK." << std::endl;

	//	// ask  for the ip the user wants to connect to
	//	std::string IP;
	//	std::cout << "Hi what's the IP that you want to connect to?" << std::endl;
	//	std::cin >> IP;

	//	// connect to socket
	//	conService.sin_addr.s_addr = inet_addr(IP.c_str()); // connect to the ipnuted IP
	//	conService.sin_family = AF_INET;
	//	conService.sin_port = htons(55555); // should the port also be the argument?

	//	if (connect(sockSocket, (SOCKADDR*)&conService, sizeof(conService)) == SOCKET_ERROR) // check for errors
	//	{
	//		std::cout << "Failed to connect: " << WSAGetLastError() << std::endl;
	//		closesocket(sockSocket);
	//		WSACleanup();
	//		return 0;
	//	}

	//	std::cout << "Connected." << std::endl;

	//	// receive messages
	//	hThread = CreateThread(NULL, 0, &ReadingThread, (void*)sockSocket, 0, &dwThreadID);
	//	if (!hThread)
	//	{
	//		std::cout << "Error at CreateThread(): " << GetLastError() << std::endl;
	//		closesocket(sockSocket);
	//		WSACleanup();
	//		return 0;
	//	}

	//	// send messages
	//	do
	//	{
	//		std::string message;
	//		if (!std::getline(std::cin, message))
	//			break;

	//		if (send(sockSocket, msg, sizeof(msg), 0) == SOCKET_ERROR)
	//		{
	//			std::cout << "Error at send(): " << WSAGetLastError() << std::endl;
	//			break;
	//		}
	//	} while (true);

	//	closesocket(sockSocket);

	//	WaitForSingleObject(hThread, INFINITE);
	//	CloseHandle(hThread);

	//	WSACleanup();
	//}

	//else
	//{
	//	std::cout << "Invalid type entered!" << std::endl;
	//	WSACleanup();
	//	return 0;
	//}

	return 0;
}