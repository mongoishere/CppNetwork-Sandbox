#pragma comment(lib, "ws2_32.lib") //required to use the winsocket functions
#include <WinSock2.h>
#include <iostream>

using namespace std;

void print_listening(char* tesft)
{
	cout << sizeof(tesft) << endl;
	cout << tesft << endl;
}

void wtf_is_dword(DWORD wtf)
{
	cout << wtf << endl;
}

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

	cout << (SOCKADDR*)&addr << endl;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0); //Create to listen to for new connection
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	listen(sListen, SOMAXCONN); // Places sListen in a state in which it is listening for an incoming connection
	cout << "listening" << endl;
	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
	if (newConnection == 0) // If accepting the client connection failed
	{
		cout << "Failed to accept the client's connection on " << endl;
	}
	else
	{
		cout << "Client connected!" << endl;
		char MOTD[256] = "Welcome! This is the Message of the day!"; //Create a buffer with message of day
		send(newConnection, MOTD, sizeof(MOTD), 0); // send MOTD buffer
	}
	system("pause");

	return 0;
}