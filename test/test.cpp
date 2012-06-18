// test.cpp: 主要專案檔。

#include "stdafx.h"
#include <cstdio>

#include <iostream>
#include <string>

#include <stdlib.h>
#include <winsock2.h>
#include <winsock.h>//dont forget to add wsock32.lib to linker dependencies

using namespace System;

int main(array<System::String ^> ^args)
{
    WSADATA			wsaData;
	
	
	SOCKET          ConnectSocket;
	SOCKADDR_IN		clientService;
	int             Port = 80;
	hostent*        remoteHost;
	char            host[60];
	bool            firstbroad;

	int             bytesSent;
	int             bytesRecv = SOCKET_ERROR;
	char            SendBuf[1024] = "";
	char            RecvBuf[1024] = "";
	
	String^			urlString = "/restful/services/yicfff/sharelink/create/";
	String^			hostString = "127.0.0.1";

	host += hostString->ToString();

	//strcat(host, hostString->ToCharArray());
	//strcat(host, urlString->ToCharArray());

	String^			httpheader = "";
	
	httpheader += "POST ";
	httpheader += urlString;
	httpheader += " HTTP/1.1\r\n";
	httpheader += "Host:";
	httpheader += hostString;
	httpheader += "\r\n";
	httpheader += "\r\n";
	//httpheader += "";

	/*
	request+="GET ";
	request+=hget;
	request+="?";
	request+=vget;
	request+=" HTTP/1.1\r\n";
    request+="Host:";
    request+= server_name;
    request+="\r\n";
    request+="\r\n";
	*/
	Console::WriteLine(httpheader);
	
	Console::WriteLine(host);
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	
	if (iResult != NO_ERROR){
		Console::WriteLine(L"Error at WSAStartup()");
	}else {
		Console::WriteLine(L"Success at WSAStartup()");
	}
	
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		Console::WriteLine("Error at socket(): "+WSAGetLastError());
		WSACleanup();
		return 0;
	}else {
		Console::WriteLine("Success at socket()");
	}
	
	setsockopt(ConnectSocket,SOL_SOCKET,SO_BROADCAST,(char *)&firstbroad,sizeof(bool));
	remoteHost = gethostbyname(host);
	clientService.sin_family = AF_INET;
	clientService.sin_port = htons( Port );

	Console::WriteLine(L"Hello World");
	//std::getchar();

	Console::ReadKey();
	return 0;
}
