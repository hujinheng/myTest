#include <WinSock2.h>
#include <iostream>
#include <time.h>
#include "test/test.pb.h"
#pragma comment (lib, "ws2_32.lib" )

using namespace std;

void startClient(int num)
{


}

void main()
{

	//1.WinSock初始化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);


	//2 建立socket
	SOCKET sClient = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	sockaddr_in ClientAddr;
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_addr.s_addr = inet_addr("192.168.1.55");//自己的本地ip地址 此处需要网络ip地址  inet_addr本地转网络 本地("XXX.XXX.XX..")-> 网络：#！@#%#
	ClientAddr.sin_port = htons(10102);// 服务端口 1~65535  一般选用10000以上 因为10000以下怕被占用


	//3 绑定
	connect( sClient, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr) );

	cout<<"客户端2启动..."<<endl;

	char szData[1024] = {0};
	int count = 0;
	Test::Person p;
	string data; 
	while( true )
	{
		//cin>>szData;
		char dest[] = "abcdefghijlkmnopqrstuvwxyz0123456709"; 
		memcpy(szData,dest,strlen(dest));
		send( sClient, szData, strlen(szData ), 0 );
		//p.set_name("asd");
		//p.set_id(3);
		//p.set_email("www.123.com");
		//p.SerializeToString(&data);
		if( strcmp( szData, "exit")== 0 )
		{
			break;
		}

		recv( sClient, szData, 1024, 0 );
		cout<<"客户端2===="<<count<<"--->"<<szData<<endl;
		count++;
		Sleep(1000);
	}


	closesocket( sClient );
	WSACleanup();
}