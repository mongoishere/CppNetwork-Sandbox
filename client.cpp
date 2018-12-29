// sockets.cpcp : Defines the entry point for the console application.
#pragma comment(lib, "ws2_32.lib") //required to use the winsocket functions
#include <WinSock2.h>
#include <iostream>

using namespace std;


int main()
{
	//Winsock startup
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) // If startup returns anything other than 0, then that means an error has occured
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr); //length of the address (required for accept call)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(9999); //Port to connect to
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0); //Set connection socket
	if (connect(Connection, (SOCKADDR*)&addr, addrlen) !=0)
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return 0; // Failed to Connect
	}
	else
	{
		cout << "Connected" << endl;
	}
	char MOTD[256];
	recv(Connection, MOTD, sizeof(MOTD), 0); // Recieve message of the dat buffer into MOTD array
	cout << "MOTD:" << MOTD << endl;
	system("pause");

	return 0;
}

