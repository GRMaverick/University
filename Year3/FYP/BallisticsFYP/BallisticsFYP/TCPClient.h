#pragma once

#include <string>
#include <iostream>
#include <WinSock2.h>

class TCPClient
{
public:
	TCPClient(void);
	TCPClient(char* ipAddress, int portNumber);
	~TCPClient(void);

	bool Connect(char* ipAddress, int portNumber);
	void Disconnect(void);

	bool SendLine(std::wstring line);
	bool SendBytes(const std::string& bytes);

private:
	SOCKET m_Socket;
};