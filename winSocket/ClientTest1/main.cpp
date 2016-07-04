#include <WinSock2.h>
#include <iostream>
#include <time.h>

#pragma comment (lib, "ws2_32.lib" )

using namespace std;



void main()
{

	//1.WinSock初始化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);


	//2 建立socket
	SOCKET sClient = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	sockaddr_in TargetAddr;//目标地址指针
	TargetAddr.sin_family = AF_INET;
	TargetAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//此处需要网络ip地址  inet_addr本地转网络 本地("XXX.XXX.XX..")-> 网络：#！@#%#
	TargetAddr.sin_port = htons(10103);// 服务端口 1~65535  一般选用10000以上 因为10000以下怕被占用

	printf("绑定ing\n");
	//3 绑定
	int a = connect( sClient, (LPSOCKADDR)&TargetAddr, sizeof(TargetAddr) );
	printf("a=================%d\n",a);
	cout<<"客户端1启动..."<<endl;

	char szData[1024] = "1234567\0";
	char sendData[1024];
	//memset(szData,0,sizeof(szData));
	//memset(sendData,0,sizeof(sendData));
	char reData[1024] = {0};
	int count = 1;
	char str[32];
	while( true )
	{
		
		//cin>>szData;
		//int szSize = strlen(szData);
		//cout<<"szSize = "<<szSize<<endl;
		//szData[szSize+1] = '\0';
		ZeroMemory(str,32);
		sprintf(reData,"%d",0);
		sprintf(str,"%d",count);
		memcpy(szData,str,sizeof(count));
		//cout<<"szSize = "<<strlen(szData)+1<<endl;
		send( sClient, szData, strlen(szData)+1, 0 );

		if( strcmp( szData, "exit")== 0 )
		{
			break;
		}
		//cout<<"========1========="<<endl;
		int r = recv( sClient, reData, 1024, 0 );
		cout<<reData<<endl;
		Sleep(1000);
		count++;
	}


	closesocket( sClient );
	WSACleanup();
}