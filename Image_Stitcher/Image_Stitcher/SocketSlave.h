#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT 1337
#define DEFAULT_IP "127.0.0.1"

using namespace std;

class SocketSlave
{
	private:


	public:
		SocketSlave();
		string read_line(SOCKET);
		void write_line(string);
		string returnline();
		void getinput();
		void getoutput();
		bool initialize();
};