#include "pch.h"
#include "TCPClient.h"

#pragma warning(disable:4996)

TCPClient::TCPClient(void)
{

}
TCPClient::TCPClient(char* ipAddress, int portNumber)
{
	Connect(ipAddress, portNumber);
}
TCPClient::~TCPClient(void)
{
	Disconnect();
}

bool TCPClient::Connect(char* ipAddress, int portNumber)
{
	WSADATA wsaData;

	int error = WSAStartup(0x0202, &wsaData);

	//----------------------
	// Initialize Winsock
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != NO_ERROR) 
	{
		wprintf(L"WSAStartup failed with error: %d\n", error);
		return false;
	}

	if (wsaData.wVersion != 0x0202)
	{
		WSACleanup();
		return false;
	}

	//----------------------
	// Create a SOCKET for connecting to server
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == INVALID_SOCKET) 
	{
		wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return false;
	}

	unsigned long mode = 1;
	ioctlsocket(m_Socket, FIONBIO, (unsigned long *)&mode);

	SOCKADDR_IN target;
	target.sin_family = AF_INET;
	target.sin_port = htons(portNumber);
	target.sin_addr.s_addr = inet_addr(ipAddress);

	error = connect(m_Socket, (SOCKADDR*)&target, sizeof(target));
	if (error == SOCKET_ERROR) 
	{
		wprintf(L"connect failed with error: %d\n", WSAGetLastError());
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}

	return true;
}
void TCPClient::Disconnect(void)
{
	int iResult = closesocket(m_Socket);
	if (iResult == SOCKET_ERROR) 
	{
		wprintf(L"close failed with error: %d\n", WSAGetLastError());
		WSACleanup();
	}
	
	WSACleanup();
}

bool TCPClient::SendLine(std::wstring line)
{
	int iResult = send(m_Socket, (const char*)line.c_str(), wcslen(line.c_str()), 0);
	if (iResult == WSAEWOULDBLOCK) 
	{
		wprintf(L"send failed with error: %d\n", WSAGetLastError());

		return false;
	}

	std::cout << "Bytes Sent: " << wcslen(line.c_str()) * sizeof(char) << std::endl; // wcslen

	return true;
}
bool TCPClient::SendBytes(const std::string& line)
{
	return false;
}