#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>



class SocketClient
{
private:
	
public:
	SocketClient();
	string read_lines(SOCKET);
	void getinput();
	void getoutput();
	//void logic();
	int iResult;
};