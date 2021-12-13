#include "SocketSlave.h"

SOCKET ConnectSocket; // Declare client socket

SocketSlave::SocketSlave()
{
	cout << "initializing socket...\n";
}
bool SocketSlave::initialize()
{
	//Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("WSAStartup Failed with error: %d\n", iResult);
		return false;
	}

	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket: %d\n", WSAGetLastError());
		WSACleanup();
		return false;
	}

	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	InetPton(AF_INET, DEFAULT_IP, &addrServer.sin_addr.s_addr);
	addrServer.sin_port = htons(DEFAULT_PORT);
	memset(&(addrServer.sin_zero), '\0', 8);

	// Connect to server.
	iResult = connect(ConnectSocket, (SOCKADDR*)&addrServer, sizeof(addrServer));
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		printf("Unable to connect to server: %d\n", WSAGetLastError());
		WSACleanup();
		return false;
	}
	return true;





}

string SocketSlave::read_line(SOCKET socket) // Function for reading lines sent by Electron JS
{
	vector<char> vector;
	char buffer;
	int bytes_received;
	int emptyCharsAllowed = 20;
	while (true) {
		
		bytes_received = recv(socket, &buffer, 1, 0);
		if (bytes_received <= 0)
		{
			return "";
		}
		if (buffer == '\n') {
			vector.push_back(buffer);
			char* pchar = new char[vector.size() + 1];
			memset(pchar, 0, vector.size() + 1);
			for (int f = 0; f < vector.size(); ++f)
				pchar[f] = vector[f];

			return pchar;
		}
		else
			vector.push_back(buffer);
	}
};
string SocketSlave::returnline()
{
	return read_line(ConnectSocket);
}
void SocketSlave::write_line(string input)
{
	send(ConnectSocket, input.c_str(), input.length(), 0);
}

void SocketSlave::getinput() // Function that reads lines and checks the server connection, runs on a separate thread
{
	string inputLine;

	while (true)
	{
		inputLine = read_line(ConnectSocket);
		if (inputLine != "") printf(inputLine.c_str());
		else break;
	}

	printf("[Input]: Connection terminated!\n");

	//exitProgram = true;
};

void SocketSlave::getoutput() // Function that sends userinput and checks the client connection, runs on a separate thread
{
	string str;

	do
	{
		getline(cin, str);
		send(ConnectSocket, str.c_str(), str.length(), 0);
	} while (str.find("exit") != 0);

	printf("[Output]: Connection terminated!\n");

	//exitProgram = true;
};