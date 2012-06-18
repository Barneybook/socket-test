// test003.cpp : 定義主控台應用程式的進入點。
//
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <stdio.h> 
#include <winsock.h>//dont forget to add wsock32.lib to linker dependencies

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
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
	
	string			filename = "Desert";
	string			urlString = "/restful/services/icfff/sharelink/create/";
	string			hostString = "124.9.14.25";
	string			oldfilename;
	string			newfilename;

	string			fullurl = hostString;
	strcpy_s(host,fullurl.c_str());

	string			httpheader = "";
	
	httpheader += "POST ";
	httpheader += urlString;
	httpheader += " HTTP/1.1\r\n";
	httpheader += "Content-Type:application/json";
	httpheader += "\r\n";
	httpheader += "Host:";
	httpheader += hostString;
	httpheader += "\r\n";

	string			json = "{\"filename\":\""+filename+"\"}";

	httpheader += "Content-Length:"; 
	ostringstream stm;
	stm << json.length();
	httpheader += stm.str();

	cout << json.length() <<endl;

	httpheader += "\r\n";
	httpheader += "\r\n";
	
	httpheader += json;

	strcpy_s(SendBuf,httpheader.c_str());

	cout << httpheader << "\n";
	//cout << host << "\n";
	
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	
	if (iResult != NO_ERROR){
		cout << "Error at WSAStartup()" << "\n";
	}else {
		//cout << "Success at WSAStartup()" << "\n";
	}
	
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (ConnectSocket == INVALID_SOCKET) {
		cout << "Error at socket():  "<< WSAGetLastError() << "\n";
		WSACleanup();
		return 0;
	}else {
		//cout << "Success at socket()" << "\n";
	}
	
	setsockopt(ConnectSocket,SOL_SOCKET,SO_BROADCAST,(char *)&firstbroad,sizeof(bool));
	remoteHost = gethostbyname(host);
	clientService.sin_family = AF_INET;
	clientService.sin_port = htons( Port );
	
	memcpy(&(clientService.sin_addr.s_addr),remoteHost->h_addr,remoteHost->h_length);
	connect(ConnectSocket,(SOCKADDR*) &clientService,sizeof(clientService));

	bytesSent = send( ConnectSocket, SendBuf, strlen(SendBuf), 0 );
	
	//system("pause");
	Sleep(100);
	string		YYY;
	string		linkvalue;

		while( bytesRecv == SOCKET_ERROR ) {
			
			bytesRecv = recv( ConnectSocket, RecvBuf, sizeof(RecvBuf), 0 );
			//cout << "bytesRecv:\n" << bytesRecv << "\n";
			/*
			int AddrLen = sizeof(struct sockaddr_in);
			sockaddr_in SenderAddr;
			bytesRecv = recvfrom( ConnectSocket, RecvBuf, sizeof(RecvBuf), 0 ,(SOCKADDR *)&SenderAddr,&AddrLen);
			*/
			YYY = RecvBuf;
			//cout << "RecvBuf:\n" << RecvBuf << "\n";
			//cout << "RecvBuf.length:\n" << YYY.length() << "\n";
			//cout << "RecvBuf:\n" << YYY << "\n";
			//YYY.substr();
			int one = YYY.find("{");
			if(one == -1){
				cout<<"沒有抓到linkvalue\n";
				break;
			}
			int two = YYY.find("}");
			//cout << "find-{:\n" << YYY.find("{") << "\n";
			//cout << "find-}:\n" << YYY.find("}") << "\n";
			
			string		json = YYY.substr(one,two-one+1);
			//cout << "json:\n" << json << "\n";

			//cout << "find-linkvalue:\n" << YYY.find("linkvalue") << "\n";
			linkvalue = YYY.substr(YYY.find("linkvalue")+12,6);
			cout << "linkvalue:\n" << linkvalue << "\n";
			

			if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
				//Form1->Memo1->Lines->Add("Connection Closed.");
				break;
			}
		}

    closesocket(ConnectSocket);
    WSACleanup();

	system("pause");

	return 0;
}

