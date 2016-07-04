#include <WinSock2.h>
#include <time.h>
#include <iostream>
//#pragma comment (lib, "ws2_32.lib" )
using namespace std;

/*
#define CHECKEND() \
{						\
	union   \
	{            \
		long a;								\
		char b;								\
	}u;							\
	u.a = 1;                     \
	if (u.b == 1)                                 \
		return 3;                             \
	else											\
		return 4;     \
}				
*/

//#define CHECKEND checkEnd()
//
//int checkEnd()
//{
//	union
//	{
//		long a;
//		char b;
//	}u;
//	u.a = 1;
//	if (u.b == 1) 
//		return 3;//小端序
//	else 
//		return 1;//大端序
//}
//
//int main()
//{
//	//cout<<checkEndEx()<<endl;
//
//	cout<<CHECKEND<<endl;
//
//}


//void error_handing(char* message)
//{
//	fputs(message,stderr);
//	fputc('\n',stderr);
//	exit(1);
//}
//
//
//#define BUFFSIZE 1024
//int main(int argc,char *argv[])
//{
//
//	
//	WSADATA wsaData;
//	WSAStartup(MAKEWORD(2,2), &wsaData);
//
//	SOCKET sServer,sClient;
//	sServer = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//
//	sockaddr_in Server_addr,Client_addr;
//	Server_addr.sin_family = AF_INET;
//	Server_addr.sin_addr.s_addr = INADDR_ANY;
//	Server_addr.sin_port = htons(10103);
//
//	bind(sServer,(LPSOCKADDR)&Server_addr,sizeof(Server_addr));
//	
//	listen(sServer,SOMAXCONN);
//
//	char mess[BUFFSIZE];
//	int str_len;
//	int adr_size = sizeof( Client_addr );
//	for (int i=0;i<5;i++)
//	{
//		sClient = accept(sServer,(LPSOCKADDR)&Client_addr,&adr_size);
//		if ( sClient == INVALID_SOCKET)
//		{
//			error_handing("ACCEPT() ERROR");
//		}
//		else
//		{
//			printf("Connected client %d \n",i+1);
//		}
//		
//		while ((str_len = recv(sClient,mess,BUFFSIZE,0))!=0)
//		{
//			send(sClient,mess,str_len,0);
//			printf("mess == %s",mess);
//		}
//		closesocket(sClient);
//	}
//
//	closesocket(sServer);
//	return 0;
//	
//	//setsockopt用法
//	//int nNetTimeout = 1000//1秒
//	//发送时限   
//	//setsockopt(socket，SOL_S0CKET,SO_SNDTIMEO，(char   *)&nNetTimeout,sizeof(int));   
//	//接收时限   
//	//setsockopt(socket，SOL_S0CKET,SO_RCVTIMEO，(char   *)&nNetTimeout,sizeof(int));
//
//	//TCP具有控制数据流功能  每次收发不允许输出缓冲区传输的值多于输入缓冲区  
//	//例如:输出缓冲区:100字节 输入缓冲区:60字节 每次发送前 输入那边的套接字会跟输出那边说最多允许发送多少个套接字 而例子中输入只有60  所以输出只能传60过去
//	// 接收缓冲区
//	//int nRecvBuf=32*1024;//设置为32K
//	//setsockopt(s,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
//	//发送缓冲区
//	//int nSendBuf=32*1024;//设置为32K
//	//setsockopt(s,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
//
//	//shutdown(socket,断开连接方式)
//	//断开连接方式:
//	//SHUT_RD    断开输入流
//	//SHUT_WR    断开输出流
//	//SHUT_RDWR 同时断开IO流
//
//
//}


//服务端socket基本同步通讯
int main()
{

	//1.WinSock初始化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	//2.建立socket
	//参数1:协议类型 一般用AF_INET 也有人用PF_INET 在windows中两者一样
	//参数2:scket类型 具体查找枚举找度娘 常用SOCK_STREAM 代表流式socket 数据像字符流一样 此参数决定数据传输的方式
	//参数3:特定协议 像TCP UDP...
	SOCKET sServer = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );//INVALID_SOCKET  SOCKET_ERROR


	sockaddr_in ServerAddr;
	ServerAddr.sin_family = AF_INET;//sa_family是地址家族，一般都是“AF_xxx”的形式。通常大多用的是都是AF_INET,代表TCP/IP协议族。
	ServerAddr.sin_addr.s_addr = INADDR_ANY;// inet_addr("192.168.100.14");//自己的ip地址 此处需要网络ip地址  inet_addr本地转网络 本地("XXX.XXX.XX..")-> 网络：#！@#%#
	ServerAddr.sin_port = htons(10103);// 服务端口 1~65535  一般选用10000以上 因为10000以下怕被占用
  //inet_addr可以验证地址真伪0~255 错误返回INADDR_NONE
  ////inet_addr和inet_aton功能一样  但inet_aton直接转化sin_addr  使用效率更高  

	//3 绑定
	bind( sServer, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );

	cout<<"服务器启动..."<<endl;

	//4 监听
	listen( sServer, 6 );

	//5 接收
	sockaddr_in AcceptSin;
	int iLen = sizeof( AcceptSin );
	SOCKET sClient = accept( sServer, (LPSOCKADDR)&AcceptSin, &iLen );

	cout<<"用户:"<<inet_ntoa( AcceptSin.sin_addr )<<"连接成功!"<<endl;

	const int n = 1024;
	char szData[n];

	char senddata[n];

	memcpy(szData,senddata,n);

	while( true )
	{
		ZeroMemory( szData, n );
		ZeroMemory( senddata, n );
		cout<<"loop 175"<<endl;
		int iRecv = recv( sClient, szData, sizeof(szData), 0 );
		cout<<"loop 177=="<<iRecv<<endl;
		if( iRecv > 0 )
		{
			

			if( strcmp( szData, "exit") == 0 )
			{
				break;
			}

			//time_t t1;
			//time( &t1 );

			//sprintf_s( szData, "%s: 收到信息", asctime( localtime(&t1) ) );
			cout<<"strlen(szData)="<<strlen(szData)<<endl;

			memcpy(senddata,szData,strlen(szData));
			//cout<<"strlen(senddata)="<<strlen(senddata)<<endl;
			send( sClient, senddata, strlen(senddata), 0 );

			cout<<inet_ntoa( AcceptSin.sin_addr )<<": "<<senddata<<endl;
				
		}
		cout<<"-------------loop 194-------------"<<endl;
	}


	closesocket( sClient );
	closesocket( sServer );

	WSACleanup();


	system("pause");
}

//------------------------------------------------------------select模型------------------------------------------------------------//
/**
*优点:占用资源少，不会消耗太多的cpu
*缺点:
select的效率和FD_SET到内核队列中的描述符的个数有关，当需要检测的描述符过多时，就要花费过多的时间去检测所有的描述符是否有时间发生，
而且可以FD_SET的描述符内核也有限制，当客户端请求成千上万时，select便无能为力。
*
**/
/*
#define PORT 9000
#define MSGSIZE 1024
int g_loop = true;
int g_iTotalConn = 0;
SOCKET g_CliSocketArr[FD_SETSIZE];//用来存放当前所有活动的客户端套接字的套接字数组
DWORD WINAPI WorkerThread(LPVOID lpParameter);
int main()
{
	WSADATA wsaData;
	SOCKET sListen,sClient;//INVALID_SOCKET  SOCKET_ERROR
	SOCKADDR_IN local,client;
	int iaddrSize = sizeof(SOCKADDR_IN);
	DWORD dwThreadld;
	//知名windows sockets api的版本号及获取特定windows sockets实现的细节
	WSAStartup(0x0202,&wsaData);//MAKEWORD(2,2)=0x0202 MAKEWORD(1,2)=0x0201
	//创建一个监听socket
	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//绑定
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//将主机数转换成无符号长整形的网络字节顺序 s_addr = S_un.S_addr
	local.sin_family = AF_INET;
	local.sin_port = htons(10103);
	
	bind( sListen, (struct sockaddr*)&local, sizeof(SOCKADDR_IN) );//LPSOCKADDR = struct sockaddr*
	cout<<"服务器启动..."<<endl;
	//开始监听
	listen(sListen,SOMAXCONN);
	
	//创建工作线程
	CreateThread(
		NULL//线程安全属性     指向SECURITY_ATTRIBUTES型态的结构的指针。在Windows 98中忽略该参数。在Windows NT中，它被设为NULL。
	   ,0//堆栈大小            用于新线程的初始堆栈大小，默认值为0。在任何情况下，Windows根据需要动态延长堆栈的大小。
	   ,WorkerThread//线程函数 指向线程函数的指标。函数名称没有限制，但是必须以下列形式声明: DWORD WINAPI ThreadProc (PVOID pParam) ;
	   ,NULL//线程参数         传递给ThreadProc的参数。这样主线程和从属线程就可以共享数据
	   ,0//线程创建属性        通常为0，但当建立的线程不马上执行时为旗标CREATE_SUSPENDED。线程将暂停直到呼叫ResumeThread来恢复线程的执行为止。
	   ,&dwThreadld//线程ID    是一个指标，指向接受执行绪ID值的变量。
	);
	
	while(g_loop)
	{
		//接受一个链接请求
		sClient = accept(sListen,(struct sockaddr*)&client,&iaddrSize);
		printf("Accepted client:%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

		//将收到的客户端套接字存放到套接字数组g_CliSocketArr中
		g_CliSocketArr[g_iTotalConn++] = sClient;
	}
    
	closesocket( sClient );
	closesocket( sListen );

	WSACleanup();
	system("pause");
	
}
DWORD WINAPI WorkerThread(LPVOID lpParam)
{
	int              i;
	fd_set      fdread;
	int            ret;
	struct timeval tv = {1,0};//指定等待时间为1秒
	char    szMessage[MSGSIZE];
	
	while(g_loop)
	{
		FD_ZERO(&fdread);//将fdread 初始化成空集合
		for (int i = 0; i < g_iTotalConn; i++)
		{
			//将所有套接字客户端套接字依次加入集合fdread
			FD_SET(g_CliSocketArr[i],&fdread);
		}
		
		//判断套接字上是否存在数据可读,这里只关心read event
		ret = select(
			0		//是一个整数值，是指集合中所有文件描述符的范围，即所有文件描述符的最大值加1，不能错！在Windows中这个参数的值无所谓，可以设置不正确

		   ,&fdread //是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的读变化的，即我们关心是否可以从这些文件中读取数据了，
					//如果这个集合中有一个文件可读，select就会返回一个大于0的值，表示有文件可读，如果没有可读的文件，则根据timeout参数再判断是否超时，
					//若超出timeout的时间，select返回0，若发生错误返回负值。可以传入NULL值，表示不关心任何文件的读变化。 

		   ,NULL	//是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的写变化的，即我们关心是否可以向这些文件中写入数据了，
					//如果这个集合中有一个文件可写，select就会返回一个大于0的值，表示有文件可写，如果没有可写的文件，则根据timeout参数再判断是否超时，
					//若超出timeout的时间，select返回0，若发生错误返回负值。可以传入NULL值，表示不关心任何文件的写变化。

		   ,NULL	//同上面两个参数的意图，用来监视文件错误异常。

		   ,&tv		//是select的超时时间，这个参数至关重要，它可以使select处于三种状态：
					//第一，若将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态，一定等到监视文件描述符集合中某个文件描述符发生变化为止；
					//第二，若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化，都立刻返回继续执行，文件无变化返回0，有变化返回一个正值；
					//第三，timeout的值大于0，这就是等待的超时时间，即 select在timeout时间内阻塞，超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。
			);
		
		//ret返回值： 
		//
		//负值：select错误
		//
		//正值：某些文件可读写或出错
		//
		//0：等待超时，没有可读写或错误的文件
		if (ret == 0)
		{
			continue;
		}

		for (int i = 0; i < g_iTotalConn; i++)
		{
			//对g_CliSocketArr中客户端套接字进行检查，判断套接字是否仍在集合中
			//select返回后,它会修改每个fdset结构,删除那些不存在待解决i/o操作的套字节句柄
			if (FD_ISSET(g_CliSocketArr[i],&fdread))
			{
				//从g_CliSocketArr[i]接收数据
				ret = recv(g_CliSocketArr[i],szMessage,MSGSIZE,0);
				//接收的数据长度为0 或者发生WSAECONNRESET错误，则标识客户端套接字主动关闭
				if(ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError()==WSAECONNRESET))
				{
					//客户端socket关闭
					printf("Client socket %d closed.\n",g_CliSocketArr[i]);
					closesocket(g_CliSocketArr[i]);
					//服务器中对应的套接字所绑定的资源释放掉,然后调整套接字数组
					if (i < g_iTotalConn - 1)
					{
						//数组中最后一个套接字挪到当前的位置上
						g_CliSocketArr[i--] = g_CliSocketArr[--g_iTotalConn];
					}
					if ((i == g_iTotalConn - 1)&& i == 0)
					{
						--g_iTotalConn;
					}
				}
				else
				{
					//从客户端接收到了数据
					szMessage[ret] = '\0';
					//将接收到的数据发回客户端
					send(g_CliSocketArr[i],szMessage,strlen(szMessage),0);
					printf("client%d:%s:\n",i,szMessage);
				}
			}
		}

	}

	
	return 0;

}
*/
//------------------------------------------------------------WSAAsyncSelect模型---------------------------------------------------------//
//******注意:此模型需要win32项目中运行*****
/*
优点：是在系统开销不大的情况下同时处理许多连接，也不需要什么集合管理。
缺点：很明显，即使你的程序不需要窗口，也要专门为 WSAAsyncSelect模型定义一个窗口。另外，让单个窗口去处理成千上万的socket操作事件，很可能成为性能瓶颈。
*/
//#include <tchar.h>
//#define PORT 10102
//#define WM_SOCKET  WM_USER+1
//#define MAX_LOADSTRING 100
//#define MSGSIZE 1024
////全局变量
//HINSTANCE hlnst;//当前实例
//TCHAR szTitle[MAX_LOADSTRING];//标题栏文本
//TCHAR szWindowClass[MAX_LOADSTRING];//主窗口类名
////此代码模块中包含的函数的前向声明
//ATOM MyRegisterClass(HINSTANCE hlnstance);
//BOOL lnitlnstance(HINSTANCE,int);
//LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);//窗口句柄，消息代码，消息代码*2
////应用程序入口
//int APIENTRY _tWinMain(HINSTANCE hlnstance,HINSTANCE hPrevlnstance, LPTSTR lpCmdLine, int nCmdShow)
//{
//	static TCHAR szAppName[] = _T("AsyncSelect Model");
//	HWND         hwnd ;
//	MSG          msg ;
//	WNDCLASS     wndclass ;
//
//	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;//窗口类风格-水平垂直重画
//	wndclass.lpfnWndProc   = WndProc ;//消息处理函数
//	wndclass.cbClsExtra    = 0 ;//类额外空间
//	wndclass.cbWndExtra    = 0 ;//窗口额外空间
//	wndclass.hInstance     = hlnstance ;//实例句柄
//	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ; //图标，读取
//	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;//光标-从文件读取
//	wndclass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH) ;//背景画刷
//	wndclass.lpszMenuName  = NULL ;//菜单名
//	wndclass.lpszClassName = szAppName;//类型
//
//	if (!RegisterClass(&wndclass))
//	{
//	MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
//	return 0 ;
//	}
//
//	hwnd = CreateWindow (szAppName,                     // window class name 类名 
//						"标题名",                   // window caption 标题名
//						WS_OVERLAPPEDWINDOW,        // window style 窗口风格 WS_SYSMENU
//						CW_USEDEFAULT,                          // initial x position  窗口位置x
//						CW_USEDEFAULT,							// initial y position  窗口位置y
//						CW_USEDEFAULT,						// initial x size 窗口位置
//						CW_USEDEFAULT,						// initial y size 窗口宽高
//						NULL,                       // parent window handle 父窗口
//						NULL,                       // window menu handle 菜单句柄
//						hlnstance,                  // program instance handle 实例句柄
//						NULL) ;                     // creation parameters 保留	
//
//	ShowWindow(hwnd, nCmdShow);
//	UpdateWindow(hwnd);
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//	TranslateMessage(&msg) ;
//	DispatchMessage(&msg) ;
//	}
//  
//	return msg.wParam;
//	
//	
//
//}
//
////处理主窗口的信息
//LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
//{
//	WSADATA wsd;
//	static SOCKET sListen;
//	SOCKET sClient;
//	SOCKADDR_IN local,client;
//	int ret,iAddrSize = sizeof(client);
//	char szMessage[MSGSIZE];
//	int wmld,wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch(message)
//	{
//		
//	case WM_CREATE:
//		//指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节
//		WSAStartup(0x0202,&wsd);
//		//创建一个侦听socket
//		sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//		//绑定
//		local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//将主机数转换成无符号长整形的网络字节顺序
//		local.sin_family = AF_INET;
//		local.sin_port = htons(PORT);
//		bind(sListen,(struct sockaddr*)&local,sizeof(local));
//		//开始监听
//		listen(sListen,3);
//		//将FD_ACCEPT消息和监听socket绑定
//		WSAAsyncSelect(sListen,hWnd,WM_SOCKET,FD_ACCEPT);
//		return 0;
//	case WM_SOCKET:
//		if (WSAGETSELECTERROR(lParam))//判断是否在套接字上发生了一个网络错误
//		{
//			//关闭发生网络错误的socket
//			closesocket(wParam);
//			break;
//		}
//
//		switch (WSAGETSELECTEVENT(lParam))
//		{
//		case FD_ACCEPT://如果收到一个客户端链接请求
//			sClient = accept(wParam,(struct sockaddr*)&client,&iAddrSize);
//
//			//接受链接请求并将sClient和FD_READ,FD_CLOSE时间绑定
//			WSAAsyncSelect(sClient,hWnd,WM_SOCKET,FD_READ|FD_CLOSE);
//			break;
//		case FD_READ://有信息可读的通知
//			ret = recv(wParam,szMessage,MSGSIZE,0);
//			if (ret == 0 || ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET)
//			{
//				//接收的数据长度为0,或者发生WSAECONNREST错误,则标识客户端套接字主动关闭
//				closesocket(wParam);
//			}
//			else
//			{
//				szMessage[ret] = '\0';
//				//将接收的数据发回客户端
//				send(wParam,szMessage,strlen(szMessage),0);
//			}
//			break;
//		case FD_CLOSE:
//			//客户端套接字关闭消息通知
//			closesocket(wParam);
//			break;
//		}
//		break;
//		
//	//case WM_COMMAND:
//	//	cout<<"WM_COMMAND"<<endl;
//		//wmld = LOWORD(wParam);
//		//wmEvent = HIWORD(wParam);
//		////分析菜单选择
//		//switch(wmld)
//		//{
//		//case IDM_EXIT:
//		//	DestroyWindow(hWnd);
//		//	break;
//		/*default:
//			return DefWindowProc(hWnd,message,wParam,lParam);
//
//		}
//		break;*/
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd,&ps);
//		//TextOut(hdc,10,10,"服务器已启动...",15);
//		EndPaint(hWnd,&ps);
//		break;
//	case WM_DESTROY:
//		//关闭监听端口
//		closesocket(sListen);
//		//清理网络环境
//		WSACleanup();
//		PostQuitMessage(0);
//		return 0;
//	default:
//		return DefWindowProc(hWnd,message,wParam,lParam);
//	}
//	return 0;
//}
//------------------------------------------------------------WSAEventSelect模型---------------------------------------------------------//
/*
优点: 该模型比起WSAAsynSelect模型的优势很明显，不需要窗口。
缺点：该模型每次只能等待64个事件，这一限制使得在处理多 socket时，有必要组织一个线程池，伸缩性不如后面要讲的重叠模型。
*/
//#include <stdio.h>
//#define PORT 10102
//#define MSGSIZE 1024
//int g_iTotalConn = 0;//用于存放当前所有活动的客户端套接字的套接字数组
//SOCKET g_CliSocketArr[MAXIMUM_WAIT_OBJECTS];//每次最多只能处理64个事件
//WSAEVENT g_CliEventArr[MAXIMUM_WAIT_OBJECTS];
//DWORD WINAPI WorkerThread(LPVOID);
//void Cleanup(int index);
//
//int main()
//{
//	WSADATA wsaData;
//	SOCKET sListen,sClient;
//	SOCKADDR_IN local,client;
//	DWORD dwThreadld;
//	int iaddrSize = sizeof(SOCKADDR_IN);
//	WSAStartup(0x0202,&wsaData);//指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节
//	//创建一个监听Socket
//	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//	//绑定
//	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//将主机数转换成无符号长整形的网络字节顺序
//	local.sin_family = AF_INET;
//	local.sin_port = htons(PORT);
//	bind(sListen,(struct sockaddr*)&local,sizeof(SOCKADDR_IN));
//
//	//开始监听
//	listen(sListen,3);
//
//	//创建工作线程
//	CreateThread(
//		NULL					//线程安全属性------指向SECURITY_ATTRIBUTES型态的结构的指针。在Windows 98中忽略该参数。在Windows NT中，它被设为NULL。
//	   ,0						//堆栈大小----------用于新线程的初始堆栈大小，默认值为0。在任何情况下，Windows根据需要动态延长堆栈的大小。
//	   ,WorkerThread			//线程函数 ---------指向线程函数的指标。函数名称没有限制，但是必须以下列形式声明: DWORD WINAPI ThreadProc (PVOID pParam) ;
//	   ,NULL					//线程参数----------传递给ThreadProc的参数。这样主线程和从属线程就可以共享数据
//	   ,0						//线程创建属性------通常为0，但当建立的线程不马上执行时为旗标CREATE_SUSPENDED。线程将暂停直到呼叫ResumeThread来恢复线程的执行为止。
//	   ,&dwThreadld				//线程ID------------是一个指标，指向接受执行绪ID值的变量。
//	);
//
//	while(true)
//	{
//		//接受一个连接请求
//		sClient = accept(sListen,(struct sockaddr*)&client,&iaddrSize);
//		printf("Accepted client==%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
//		//将收到的客户端套接字存放到套接字数组g_CliSocketArr中
//		g_CliSocketArr[g_iTotalConn] = sClient;
//		g_CliEventArr[g_iTotalConn]  = WSACreateEvent();//WSACreateEvent函数的返回值很简单,就是一个创建好的事件对象句柄
//		//注册接收到的客户端socket感兴趣的网络事件类型
//		WSAEventSelect
//		(
//			g_CliSocketArr[g_iTotalConn],//关联的套接字
//			g_CliEventArr[g_iTotalConn],//关联的事件句柄
//			FD_READ|FD_CLOSE//事件类型
//		);
//		g_iTotalConn++;
//
//	}
//}
//
//DWORD WINAPI WorkerThread(LPVOID lpParam)
//{
//	int				 ret,index;
//	WSANETWORKEVENTS NetworkEvents;
//	char             szMessage[MSGSIZE];
//
//	while(true)
//	{
//		//等待网络事件 触发 事件对象句柄的工作状态,最多可等待一个网络事件发生为1秒
//		ret = WSAWaitForMultipleEvents
//			(
//			// g_iTotalConn和g_CliEventArr参数定义了由WSAEVENT对象构成的一个数组(WSACreateEvent()这个方法所组成的一个数组)
//			g_iTotalConn,//事件对象的数量
//			g_CliEventArr,//一个指针 用于直接应用该数组 此处注意:WSAWaitForMultipleEvents只能支持由WSA_MAXIMUM_WAIT_EVENTS对象规定(也就是MAXIMUM_WAIT_OBJECTS)的一个最大值64 假如想让这个模型同时管理不止64个套接字,必须创建额外的工作线程
//			false,//参数指定了WSAWaitForMultipleEvents如何等待在事件数组中的对象.若设为true,那么只等g_CliEventArr数组内报的所有事件对象都已经进入"已通知"状态,函数才会返回 若设为false 任何一个事件对象进入"已通知"状态,函数就会返回. 一般设为false保证程序及时响应处理
//			1000,//规定最多可等待一个网络事件发生有多长事件,以毫秒为单位 这是一项"超时"设定,超过规定事件,函数就会立即返回,即使由fWaitAll(上面的参数)规定的条件尚未满足也是如此.如超时设为0,函数会检测指定的事件对象的状态,并立即返回.这样一来,应用程序实际便可实现对事件对象的"轮询".但是考虑它对性能造成的影响,还是尽量避免设0
//			false//此参数在使用WSAEventSelect模型时候是可以忽略的,且应设为false
//			);
//
//		if (ret == WSA_WAIT_FAILED || ret == WSA_WAIT_TIMEOUT)
//		{
//			//如果超时或者失败
//			continue;
//		}
//		//得到网络事件 触发 事件socket的索引位置
//		index = ret - WSA_WAIT_EVENT_0;
//		//调查触发事件socket具体发生了什么类型的网络事件
//		WSAEnumNetworkEvents
//			(
//			 g_CliSocketArr[index]//套接字
//			,g_CliEventArr[index]	//参数可选,它指定了一个事件句柄,对于打算重置的那个事件对象.由于事件对象处在一个"已通知"状态,所以可将它传入,令其自动成为"未通知状态". 如果不想用这个参数来重置事件 那么可以使用WSAResetEvent函数
//			,&NetworkEvents	//一个指针,指向WSANETWORKEVENTS结构,用于接收套接字上发生的网络事件类型以及可能出现的任何错误代码.
//			);
//
//		//在当前套接字上处理读取事件
//		if (NetworkEvents.lNetworkEvents & FD_READ)
//		{
//			//如果是FD_READ事件发生,说明收到了客户端发送来的数据
//			ret = recv(g_CliSocketArr[index],szMessage,MSGSIZE,0);//注意:此处是和重叠IO区别根本原因  需要再一次从缓存区读取出来
//			//接收的数据长度为0,或者发生WSAECONNRESET错误,则表示客户端套接字主动关闭
//			if (ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET))
//			{
//				//清除关闭index对应的socket
//				Cleanup(index);
//			}
//			else
//			{
//				szMessage[ret] = '\0';
//				printf("返回client = %d:%s\n",index,szMessage);
//				//将接收到的数据发回客户端
//				send(g_CliSocketArr[index],szMessage,strlen(szMessage),0);
//			}
//		}
//
//		//当前产生事件的套接字,如果是客户端关闭事件
//		if ( NetworkEvents.lNetworkEvents & FD_CLOSE )
//		{
//			Cleanup(index);
//		}
//	}
//
//	return 0;
//
//}
//void Cleanup(int index)
//{
//	//关闭g_CliSocketArr[index]记录的socket
//	closesocket(g_CliSocketArr[index]);
//	//释放由事件句柄g_CliEventArr[index]使用的系统资源
//	WSACloseEvent(g_CliEventArr[index]);
//
//	if ( index < g_iTotalConn - 1 )
//	{
//		//数组中最后一个套接字挪到当前的位置上
//		g_CliSocketArr[index] = g_CliSocketArr[g_iTotalConn-1];
//		g_CliEventArr[index] = g_CliEventArr[g_iTotalConn-1];
//	}
//	g_iTotalConn--;
//}
//---------------------------------------------------------------------------------------------------------------------//
/*
优点:1.可以运行在支持Winsock2的所有Windows平台 ,而不像完成端口只是支持NT系统(xp win7 win8...)。
2.比起阻塞、select、WSAAsyncSelect以及WSAEventSelect等模型，重叠I/O(Overlapped I/O)模型使应用程序能达到更佳的系统性能。
3.重叠模型与上述4种模型根本区别在于：
因为它和这4种模型不同的是，使用重叠模型的应用程序通知缓冲区收发系统直接使用数据，也就是说，
如果应用程序投递了一个10KB大小的缓冲区来接收数据，且数据已经到达套接字，则该数据将直接被拷贝到投递的缓冲区。

而这4种模型种，数据到达并拷贝到单套接字接收缓冲区中，此时应用程序会被告知可以读入的容量。
当应用程序调用接收函数之后，数据才从单套接字缓冲区拷贝到应用程序的缓冲区，差别就体现出来了。

简单的说 重叠模型在接收到数据时候就把东西放入缓存区 放入完成时候直接拷贝到应用程序缓冲区 并且告知用户接收(完成例程有 事件通知没有)  
而其他4个模型则需要调用接收函数之后 数据才从缓冲区拷贝到应用程序缓冲区中
*/
//------------------------------------------------------------OverLapped模型(事件通知)---------------------------------------------------------//
/*
优点: 可以同时等待多个事件 直接去指定缓存区取数据
缺点:需要自己去维护重叠结构数组 实现难度是所有模型最高 异步选择<选择<完成里程实现重叠i/o<事件选择<完成端口<事件通知实现重叠i/o
单线程最多只能等待64个socket事件，多线程下增加了CPU上下文切换的开销
*/
//#include <stdio.h>
//#define PORT 10102
//#define MSGSIZE 1024
//typedef struct
//{
//	WSAOVERLAPPED overlap;
//	WSABUF Buffer;
//	char szMessage[MSGSIZE];
//	DWORD NumberOfBytesRecvd;
//	DWORD Flags;
//}PER_IO_OPERATION_DATA,*LPPER_IO_IPERATION_DATA;//重叠结构，用于接收通知时获取数据。 
//
//int g_iTotalConn = 0;
//
////用来存放当前所有活动的客户端套接字的套接字数组
//SOCKET g_CliSocketArr[MAXIMUM_WAIT_OBJECTS];
//WSAEVENT g_CliEventArr[MAXIMUM_WAIT_OBJECTS];
//LPPER_IO_IPERATION_DATA g_pPerIODataArr[MAXIMUM_WAIT_OBJECTS];
//
//DWORD WINAPI WorkerThread(LPVOID);
//
//void Cleanup(int);
//
//int main()
//{
//	WSADATA wsaData;
//	SOCKET sListen,sClient;
//	SOCKADDR_IN local,client;
//	DWORD dwThreadid;
//	int iaddrSize = sizeof(SOCKADDR_IN);
//	//指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节
//	WSAStartup(0x0202,&wsaData);
//	//创建一个监听socket
//	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//	//绑定
//	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	local.sin_family = AF_INET;
//	local.sin_port = htons(PORT);
//	bind(sListen,(struct sockaddr*)&local,sizeof(SOCKADDR_IN));
//	//开始监听
//	listen(sListen,3);
//	//创建工作线程
//	CreateThread(NULL,0,WorkerThread,NULL,0,&dwThreadid);
//
//	while(true)
//	{
//		//接受一个链接请求
//		sClient = accept(sListen,(struct sockaddr*)&client,&iaddrSize);
//		printf("Accepted client:%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
//		g_CliSocketArr[g_iTotalConn] = sClient;
//
//		//分配一个新的PER_IO_OPERATION_DATA结构体
//		g_pPerIODataArr[g_iTotalConn] = (LPPER_IO_IPERATION_DATA)HeapAlloc
//			(
//				GetProcessHeap(),
//				HEAP_ZERO_MEMORY,
//				sizeof(PER_IO_OPERATION_DATA)
//			);
//		g_pPerIODataArr[g_iTotalConn]->Buffer.len = MSGSIZE;
//		g_pPerIODataArr[g_iTotalConn]->Buffer.buf = g_pPerIODataArr[g_iTotalConn]->szMessage;
//		g_CliEventArr[g_iTotalConn] = g_pPerIODataArr[g_iTotalConn]->overlap.hEvent = WSACreateEvent();
//		//在套接字上投递一个异步WSARecv请求,指定参数为WSAOVERLAPPED结构
//		WSARecv(g_CliSocketArr[g_iTotalConn],//socket套接字
//			&g_pPerIODataArr[g_iTotalConn]->Buffer,//接收到的内容数据会放在这个缓存数组里 再通过WSAWaitForMultipleEvents（...）接收到该事件通知
//			1,// 数组中WSABUF结构的数量
//			&g_pPerIODataArr[g_iTotalConn]->NumberOfBytesRecvd,// 如果接收操作立即完成，这里会返回函数调用所接收到的字节数
//			&g_pPerIODataArr[g_iTotalConn]->Flags, // 和函数socket()一样，和用来控制套接字的行为，例如，指出当前套接字是面向流的还是面向消息的。通常设置为0。 MSG_PEEK、MSG_OOB、MSG_PARTIAL
//			&g_pPerIODataArr[g_iTotalConn]->overlap, // “绑定”的重叠结构。非重叠操作（或非异步操作）可忽略
//			NULL// 完成例程中将会用到的参数(回调函数地址)，我们这里设置为 NULL 
//			);
//		g_iTotalConn++;
//	}
//
//	closesocket(sListen);
//	WSACleanup();
//	return 0;
//	
//}
//
//DWORD WINAPI WorkerThread(LPVOID lpParam)
//{
//	int ret,index;
//	DWORD cbTransferred;
//	while(true)
//	{
//		//等待与重叠调用关联在一起的事件进入"已通知"状态,最多可等待一个网络事件发生为1秒
//		ret = WSAWaitForMultipleEvents(g_iTotalConn,g_CliEventArr,FALSE,1000,FALSE);
//		if (ret == WSA_WAIT_FAILED || ret == WSA_WAIT_TIMEOUT)
//		{
//			//如果超时或失败
//			continue;
//		}
//
//		index = ret - WSA_WAIT_EVENT_0;
//		WSAResetEvent(g_CliEventArr[index]);//重叠事件对象,对完成的重叠请求进行处理
//		WSAGetOverlappedResult( //判断重叠调用的返回状态是什么
//			g_CliSocketArr[index],//与之对应的套接字
//			&g_pPerIODataArr[index]->overlap,//对应于重叠操作开始时,指定的那个WSAOVERLAPPED结构
//			&cbTransferred,//对应一个DWORD 负责接收一次重叠发送或接收操作实际传输的字节数
//			true,//决定函数是否应该等待一次待决定的重叠操作完成 true:除非操作完成否则函数不会返回 false：操作仍然处于待决定状态，那么WSAGetOverlappedResult函数返回false值 同时返回一个WSAIOINCOMPLETE（I/O操作未完成）错误。但就目前情况来说,由于需要等待重叠操作的一个已通知事件完成，所以该参数无论采用什么设置，都没任何效果
//			&g_pPerIODataArr[g_iTotalConn]->Flags//对应于一个指针,指向一个DWORD,负责接收结果标志(加入原先的重叠调用是用WSARecv或WSARecvFrom函数发出的)。如WSAGetOverlappedResult函数调用成功,返回值就是true。这意味重叠重叠I/O操作已成功完成,而且由lpcbTransfer参数指向的值已进行了更新。若返回值
//			);
//		if (cbTransferred == 0)
//		{
//			//负责接收一次重叠接收操作实际传输的字节数为0.意味着客户端已经关闭了链接
//			Cleanup(index);
//		}
//		else
//		{
//			//g_pPerIODataArr[index]->szMessage包含了接收到的数据
//			g_pPerIODataArr[index]->szMessage[cbTransferred] = '\0';
//			//将数据发回客户端
//			send(g_CliSocketArr[index]
//				,g_pPerIODataArr[index]->szMessage//应用程序要发送的数据的缓冲区(想要发送的数据)
//				,cbTransferred,//实际要发送的字节数
//				0//一般置为0即可
//				);
//			//在套接字上投递另一个重叠WSARecv请求
//				WSARecv(
//					g_CliSocketArr[index],
//					&g_pPerIODataArr[index]->Buffer,
//					1,
//					&g_pPerIODataArr[index]->NumberOfBytesRecvd,
//					&g_pPerIODataArr[index]->Flags,
//					&g_pPerIODataArr[index]->overlap,
//					NULL
//					);
//				printf("client%d:%s:\n",index,g_pPerIODataArr[index]->szMessage);
//		}
//	}
//	return 0;
//}
//
//void Cleanup(int index)
//{
//	//关闭g_CliSocketArr[index]记录的socket
//	closesocket(g_CliSocketArr[index]);
//	//释放由事件句柄g_CliEventArr[index]使用的系统资源
//	WSACloseEvent(g_CliEventArr[index]);
//	//释放PER_IO_OPERATION_DATA结构体g_pPerIODataArr[index]占用的资源
//	HeapFree(GetProcessHeap(),0,g_pPerIODataArr[index]);
//	if (index < g_iTotalConn - 1)
//	{
//		//数组中最后一个套接字挪到当前的位置上
//		g_CliSocketArr[index] = g_CliSocketArr[g_iTotalConn - 1];
//		g_CliEventArr[index] = g_CliEventArr[g_iTotalConn - 1];
//		g_pPerIODataArr[index] = g_pPerIODataArr[g_iTotalConn - 1];
//	}
//	g_pPerIODataArr[--g_iTotalConn] = NULL;
//}
//------------------------------------------------------------CompletionRoutne模型(完成例程)---------------------------------------------------------//
/*
//如果辅助线程不调用SleepEx，则内核在完成一次I/O操作后，无法调用完成例程（因为完成例程的运行应该和当初激活WSARecv异步操作的代码在同一个线程之内）。
//当重叠IO操作完成，SleepEx会被完成的消息唤醒，从而使得辅助线程中的完成例程得到执行。
//优点:与事件通知重叠IO相比 没有链接限制 并且简单
//少了单线程最多只能处理64个事件的限制，减少多线程上下文切换的开销
//缺点:没有CPU的负载均衡 哪个线程请求就哪个线程处理，这样会存在个别CPU核空闲着，而个别CPU核又很吃紧的情况
就是发出请求的线程必须得要自己去处理接收请求，
哪怕是这个线程发出了很多发送或者接收数据的请求，但是其他的线程都闲着…，
这个线程也还是得自己来处理自己发出去的这些请求，没有人来帮忙…这就有一个负载均衡问题，显然性能没有达到最优化。
*/
//#define PORT 10102
//#define MSGSIZE 1024
//
//typedef struct
//{
//	WSAOVERLAPPED overlap;
//	WSABUF Buffer;
//	char szMessage[MSGSIZE];
//	DWORD NumberOfBytesRecvd;
//	DWORD Flags; //完成状态的附加标志位
//	SOCKET sClient;
//}PER_IO_OPERATION_DATA,*LPPER_IO_OPERATION_DATA;//重叠结构，用于接收通知时获取数据。 
//
//DWORD WINAPI WorkerThread(LPVOID);
//
//void CALLBACK CompletionROUTINE(DWORD,DWORD,LPWSAOVERLAPPED,DWORD);
//SOCKET g_sNewClientConnection;
//BOOL g_bNewConnectionArrived = false;
//
//int main()
//{
//	WSADATA wsaData;
//	SOCKET sListen;
//	SOCKADDR_IN local,client;
//	DWORD dwThreadid;
//	int iaddrSize = sizeof(SOCKADDR_IN);
//	//指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节
//	WSAStartup(0x0202,&wsaData);
//	//创建一个监听socket
//	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//
//	//绑定
//	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	local.sin_family = AF_INET;
//	local.sin_port = htons(PORT);
//	bind(sListen,(struct sockaddr *)&local,sizeof(SOCKADDR_IN));
//
//	//开始监听
//	listen(sListen,3);
//	//创建工作线程
//	CreateThread(NULL,0,WorkerThread,NULL,0,&dwThreadid);
//
//	while(true)
//	{
//		//接受一个链接请求
//		g_sNewClientConnection = accept(sListen,(struct sockaddr*)&client,&iaddrSize);
//		g_bNewConnectionArrived = true;
//		printf("Accepted client:%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
//	}
//}
//
//DWORD WINAPI WorkerThread(LPVOID lpParam)
//{
//	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;
//	while(true)
//	{
//		if(g_bNewConnectionArrived)
//		{
//			//分配一个新的PER_IO_OPERATION_DATA结构体
//			lpPerIOData = (LPPER_IO_OPERATION_DATA)HeapAlloc(
//				GetProcessHeap(),
//				HEAP_ZERO_MEMORY,
//				sizeof(PER_IO_OPERATION_DATA)
//				);
//			lpPerIOData->Buffer.len = MSGSIZE;
//			lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
//			lpPerIOData->sClient = g_sNewClientConnection;
//			//在套接字上投递一个异步WSARecv请求,指定参数为WSAOVERLAPPED结构
//			//同时提供一个完成例程CompletionROUTINE
//			WSARecv(
//				lpPerIOData->sClient,
//				&lpPerIOData->Buffer,
//				1,
//				&lpPerIOData->NumberOfBytesRecvd,
//				&lpPerIOData->Flags,
//				&lpPerIOData->overlap,
//				CompletionROUTINE
//				);
//
//			g_bNewConnectionArrived = false;
//		}
//		//使用SleepEx函数将自己的线程置为一种可警告等待状态
//		SleepEx(
//			1000//sleepEx函数的等待事件,以毫秒为单位。加入将要这个参数设置INFINITE(0xFFFFFFFF)那么SleepEx会无休止的等待下去
//			,true
//			//规定一个完成例程的执行方式。假如设置为false，而且进行了一次IO完成回调，那么IO完成函数不会执行，而且函数不会返回，除非超过由上面参数的规定事件。
//			//若设置true 那么完成例程会得到执行，同时SleepEx函数返回WAIT_IO_COMPLETION
//			);
//		//返回值：
//		//Sleep函数无返回值，SleepEx返回0表示时间间隔完成，返回WAIT_IO_COMPLETION表示I/O完成回调函数被调用
//	}
//	return 0;
//}
//
//void CALLBACK CompletionROUTINE(
//								DWORD dwError,//重叠操作(由lpOverlapped指定)的完成状态是什么
//								DWORD cbTransferred,//重叠操作期间 实际传输的字节量是多大
//								LPWSAOVERLAPPED lpOverlapped,//指定的是传递到最初的IO调用内的一个WSAOVERLAPPED结构
//								DWORD dwFlags//目前尚未使用 设为0
//								)
//{
//	LPPER_IO_OPERATION_DATA lpPerIOData = (LPPER_IO_OPERATION_DATA)lpOverlapped;
//
//	if (dwError != 0 || cbTransferred == 0)
//	{
//		//负责接收一次重叠接收操作实际传输的字节数为0.意味着客户端已经关闭了链接
//		closesocket(lpPerIOData->sClient);//关闭lpPerIOData->sClientd代表套接字
//		//释放lpPerIOData占用的资源
//		HeapFree(GetProcessHeap(),0,lpPerIOData);
//
//	}
//	else
//	{
//		//lpPerIOData->szMessage包含了接收到的数据
//		lpPerIOData->szMessage[cbTransferred] = '\0';
//		//将数据发回客户端
//		send(lpPerIOData->sClient,lpPerIOData->szMessage,cbTransferred,0);
//		printf("client:%s\n",lpPerIOData->szMessage);
//
//		memset(&lpPerIOData->overlap,0,sizeof(WSAOVERLAPPED));
//		lpPerIOData->Buffer.len = MSGSIZE;
//		lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
//		//投递另一个重叠WSARecv请求
//		WSARecv(
//			lpPerIOData->sClient,
//			&lpPerIOData->Buffer,
//			1,
//			&lpPerIOData->NumberOfBytesRecvd,
//			&lpPerIOData->Flags,
//			&lpPerIOData->overlap,
//			CompletionROUTINE
//			);
//
//	}
//}
//---------------------------------------------------------------------------------------------------------------------------------------//
/*
对比上面几种机制，完成端口的做法是这样的：事先开好几个线程，你有几个CPU我就开几个，首先是避免了线程的上下文切换，
因为线程想要执行的时候，总有CPU资源可用，然后让这几个线程等着，等到有用户请求来到的时候，就把这些请求都加入到一个公共消息队列中去，
然后这几个开好的线程就排队逐一去从消息队列中取出消息并加以处理，这种方式就很优雅的实现了异步通信和负载均衡的问题，
因为它提供了一种机制来使用几个线程“公平的”处理来自于多个客户端的输入/输出，并且线程如果没事干的时候也会被系统挂起，
不会占用CPU周期，挺完美的一个解决方案，不是吗？哦，对了，这个关键的作为交换的消息队列，就是完成端口。
相关资料:http://blog.csdn.net/piggyxp/article/details/6922277
*/
//------------------------------------------------------------IOCP模型(完成端口)---------------------------------------------------------//
/*
优点:在完成例程基础上+使用CPU负载均衡，充分利用CPU各核
缺点:比较复杂
*/
/*完成端口基本模型
#define PORT 10102
#define MSGSIZE 1024
typedef enum
{
	RECV_POSTED
}OPERATION_TYPE;

typedef struct
{
	WSAOVERLAPPED overlap;
	WSABUF Buffer;
	char szMessage[MSGSIZE];
	DWORD NumberOfBytesRecvd;
	DWORD Flags;
	OPERATION_TYPE OperationType;
}PER_IO_OPERATION_DATA,*LPPER_IO_OPERATION_DATA;

DWORD WINAPI WorkerThread(LPVOID);

int main()
{
	WSADATA wsaData;
	SOCKET sListen,sClient;
	SOCKADDR_IN local,client;
	DWORD i,dwThreadid;
	int iaddrSize = sizeof(SOCKADDR_IN);
	HANDLE CompletionPort = INVALID_HANDLE_VALUE;
	SYSTEM_INFO systeminfo;
	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;
	//指明Windows Sockets API版本号及获取特定Windows Sockets实现的细节
	WSAStartup(0x0202,&wsaData);
	
	//创建完成端口对象
	CompletionPort = CreateIoCompletionPort(//作用:1.用于创建一个完成对口对象 2.将一个句柄同完成端口关联到一起
		INVALID_HANDLE_VALUE//指定一个要同完成端口关联在一起的套接字句柄
		,NULL//指定的是一个现有的完成端口
		,0//指定要与某个特定套接字句柄关联在一起的“单句柄数据”。在这个参数中，应用程序可保存与一个套接字对应的任意类型的信息。
		//之所以把它叫作“单句柄数据”，是由于它只对应着与那个套接字句柄关联在一起的数据。可将其作为指向一个数据结构的指针，来保存套接字句柄；在那个结构中，同时包含了套接字的句柄，以及与那个套接字有关的其他信息
		,0//并发线程的数量 顶一个了在一个完成端口上同时允许执行到的线程数量 理想情况下希望每个处理器各自负责一个线程的运行,为完成端口提供服务,避免国语频繁的线程切换
		//若将该参数设为0 说明系统内安装了多少个处理器 便允许同时运行多少个线程
		); 
	//CreateIoCompletionPort返回一个句柄 为完成端口分配了一个套接字句柄后 用来对那个端口进行标定(引用)

	//获得系统信息
	GetSystemInfo(&systeminfo);
	for(i=0;i<systeminfo.dwNumberOfProcessors;i++)//这里建立的线程数最好是CPU数的两倍 即systeminfo.dwNumberOfProcessors * 2
	{
		//通过系统信息中给出的CPU的个数创建工作者线程
		CreateThread(NULL,0,WorkerThread,CompletionPort,0,&dwThreadid);//这里把CompletionPort传递给ThreadProc的参数。这样主线程和从属线程就可以共享数据
	}
	//创建一个监听socket
	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//绑定
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//将主机数转换成无符号长整形的网络字节顺序
	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);//运用端口
	bind(sListen,(struct sockaddr*)&local,sizeof(SOCKADDR_IN));
	//开始监听
	listen(sListen,3);
	
	while(TRUE)//程序进入循环
	{
		//接收一个客户端连接
		sClient = accept(sListen,(struct sockaddr*)&client,&iaddrSize);
		printf("Accepted client:%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		//将该客户端套接字与完成端口绑定到一起
		CreateIoCompletionPort(//创建完成端口对象
			(HANDLE)sClient//指定一个要同完成端口关联在一起的套接字句柄
			,CompletionPort//指定的是一个现有的完成端口
			,(DWORD)sClient//指定要与某个特定套接字句柄关联在一起的“单句柄数据”。
			,0//并发线程的数量
			);
		//在新收到的链接上发起一个异步操作
		lpPerIOData = (LPPER_IO_OPERATION_DATA)HeapAlloc(
			GetProcessHeap()
			,HEAP_ZERO_MEMORY
			,sizeof(PER_IO_OPERATION_DATA)
			);
		lpPerIOData->Buffer.len = MSGSIZE;
		lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
		lpPerIOData->OperationType = RECV_POSTED;
		//异步调用WSARecv,这次用到"尾随数据",使接收数据所用的缓冲区紧跟在WSAOVERLAPPED对象之后
		WSARecv(
			sClient//socket套接字
		   ,&lpPerIOData->Buffer//接收到的内容数据会放在这个缓存数组里 再通过WSAWaitForMultipleEvents（...）接收到该事件通知
		   ,1// 数组中WSABUF结构的数量
		   ,&lpPerIOData->NumberOfBytesRecvd// 如果接收操作立即完成，这里会返回函数调用所接收到的字节数
		   ,&lpPerIOData->Flags// 和函数socket()一样，和用来控制套接字的行为，例如，指出当前套接字是面向流的还是面向消息的。通常设置为0。 MSG_PEEK、MSG_OOB、MSG_PARTIAL
		   ,&lpPerIOData->overlap// “绑定”的重叠结构。非重叠操作（或非异步操作）可忽略
		   ,NULL// 完成例程中将会用到的参数(回调函数地址)，我们这里设置为 NULL 
		   );
	}

	//向每个工作者线程都发一个特殊的完成数据包。指示每个线程都"立即结束并退出"
	PostQueuedCompletionStatus(CompletionPort,0xFFFFFFFF,0,NULL);
	//关闭完成端口对象
	CloseHandle(CompletionPort);
	WSACleanup();
	return 0;
}


DWORD WINAPI WorkerThread(LPVOID CompletionPortID)
{
	HANDLE CompletionPort = (HANDLE)CompletionPortID;//完成端口
	DWORD dwBytesTransferred;
	SOCKET sClient;
	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;

	while(TRUE)
	{
		//取得本次I/O的相关信息
		GetQueuedCompletionStatus(//接收调用的结果 获取排队完成状态函数
			CompletionPort,//IOCP 对应于在上面等待的完成端口
			&dwBytesTransferred,//收到数据大小 完成一次io操作后(WSASend或WSARecv) 接收实际传输的字节数
			(PULONG_PTR)&sClient,//发送数据socket 原先传递进入CreateIoCompletionPort函数的套接字返回"单据并数". 大家最好将套接字句柄保存在这个"键"中
			(LPOVERLAPPED*)&lpPerIOData,//用于接收完成的IO操作重叠结果,这实际是一个相当重要的参数,因为要用它获取每个IO操作的数据
			INFINITE//用于指定调用者希望等待一个完成数据包在完成端口上出现的事件。假如将其设为INFINITE 调用会无休止等下去
			);

		if(dwBytesTransferred == 0xFFFFFFFF)
		{
			return 0;
		}
		if(lpPerIOData->OperationType == RECV_POSTED)
		{
			if ( dwBytesTransferred == 0 )
			{
				closesocket(sClient);//关闭套接字sClient
				//释放lpPerIOData占用的资源
				HeapFree(GetProcessHeap(),0,lpPerIOData);
			}
			else
			{
				//通过单机IO数据结构找到接收数据缓冲区,然后将数据原封不懂地发送到客户端
				lpPerIOData->szMessage[dwBytesTransferred] = '\0';
				send(sClient,lpPerIOData->szMessage,dwBytesTransferred,0);
				printf("client:%s\n",lpPerIOData->szMessage);
				//再次触发一个WSARecv异步操作
				memset(lpPerIOData,0,sizeof(PER_IO_OPERATION_DATA));
				lpPerIOData->Buffer.len = MSGSIZE;
				lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
				lpPerIOData->OperationType = RECV_POSTED;
				WSARecv(
					sClient,//socket套接字
					&lpPerIOData->Buffer,//接收到的内容数据会放在这个缓存数组里 再通过WSAWaitForMultipleEvents（...）接收到该事件通知
					1,// 数组中WSABUF结构的数量
					&lpPerIOData->NumberOfBytesRecvd,// 如果接收操作立即完成，这里会返回函数调用所接收到的字节数
					&lpPerIOData->Flags,// 和函数socket()一样，和用来控制套接字的行为，例如，指出当前套接字是面向流的还是面向消息的。通常设置为0。 MSG_PEEK、MSG_OOB、MSG_PARTIAL
					&lpPerIOData->overlap,// “绑定”的重叠结构。非重叠操作（或非异步操作）可忽略
					NULL// 完成例程中将会用到的参数(回调函数地址)，我们这里设置为 NULL 
					);
			}
		}
	}

	return 0;
}
*/
//------------------------------------------------------------完成端口进阶模型---------------------------------------------------------//
//#define PORT 10102
//#define MSGSIZE 1024
//#include "Mswsock.h"

/*
typedef enum
{
	SEND,
	RECV,
	ACCEPT
}OPERATION_TYPE;
//单句柄数据定义
typedef struct _PER_HANDLE_DATA
{
     SOCKET socket;     //相关的套接字
     SOCKADDR_STORAGE clientAddr;     //客户端的地址
}PER_HANDLE_DATA,*LPPER_HANDLE_DATA;
typedef struct
{
	OVERLAPPED    	overlap;
	WSABUF			Buffer;
	char			szMessage[MSGSIZE];
	DWORD			NumberOfBytesRecvd;
	DWORD			Flags;
	OPERATION_TYPE  OperationType;
	SOCKET			sockAccept;          // 这个I/O操作所使用的Socket，每个连接的都是一样的  
}PER_IO_OPERATION_DATA,*LPPER_IO_OPERATION_DATA;


DWORD WINAPI WorkerThread(LPVOID);

int main()
{
	//创建完成端口对象
	HANDLE CompletionPort = CreateIoCompletionPort(//作用:1.用于创建一个完成对口对象 2.将一个句柄同完成端口关联到一起
		INVALID_HANDLE_VALUE//指定一个要同完成端口关联在一起的套接字句柄
		,NULL//指定的是一个现有的完成端口
		,0//指定要与某个特定套接字句柄关联在一起的“单句柄数据”。在这个参数中，应用程序可保存与一个套接字对应的任意类型的信息。
		//之所以把它叫作“单句柄数据”，是由于它只对应着与那个套接字句柄关联在一起的数据。可将其作为指向一个数据结构的指针，来保存套接字句柄；在那个结构中，同时包含了套接字的句柄，以及与那个套接字有关的其他信息
		,0//并发线程的数量 在一个完成端口上同时允许执行到的线程数量 理想情况下希望每个处理器各自负责一个线程的运行,为完成端口提供服务,避免频繁的线程切换
		//若将该参数设为0 说明系统内安装了多少个处理器 便允许同时运行多少个线程
		); 
	//CreateIoCompletionPort返回一个句柄 为完成端口分配了一个套接字句柄后 用来对那个端口进行标定(引用)

	
	//获得系统信息
	SYSTEM_INFO systeminfo;
	GetSystemInfo(&systeminfo);
	int m_nThreads = systeminfo.dwNumberOfProcessors*2;//这里建立的线程数最好是CPU数的两倍 即systeminfo.dwNumberOfProcessors * 2
	DWORD dwThreadid;
	for(int i=0;i<m_nThreads;i++)
	{
		//通过系统信息中给出的CPU的个数创建工作者线程
		HANDLE thread = CreateThread(NULL,0,WorkerThread,CompletionPort,0,NULL);//这里把CompletionPort传递给ThreadProc的参数。这样主线程和从属线程就可以共享数据
		CloseHandle(thread);
	}

	//指明Windows Sockets API版本号及获取特定Windows Sockets实现的细节
	WSADATA wsaData;
	WSAStartup(0x0202,&wsaData);
	unsigned int i;
	//初始化Socket
	sockaddr_in ServerAddress;
	//创建一个监听socket
	//WSASocket只有windows下特有的API不具备跨平台 socket是跨平台(由于完成端口只是微软独有 所以无需考虑)
	SOCKET m_sockListen = WSASocket(AF_INET,SOCK_STREAM,0,NULL, 0, WSA_FLAG_OVERLAPPED);
	// 填充地址结构信息  
	ZeroMemory((char *)&ServerAddress, sizeof(ServerAddress));  
	ServerAddress.sin_family = AF_INET;  
	// 这里可以选择绑定任何一个可用的地址，或者是自己指定的一个IP地址   
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);                        
	//ServerAddress.sin_addr.s_addr = inet_addr(“你的IP”);   //inet_aton直接转化sin_addr  使用效率更高      
	ServerAddress.sin_port = htons(PORT);  
	
	// 绑定端口  
	bind(m_sockListen,(struct sockaddr*)&ServerAddress,sizeof(ServerAddress));


	//将监听套接字与完成端口绑定
     LPPER_HANDLE_DATA perDandleData;
     perDandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR,sizeof(PER_HANDLE_DATA));
     perDandleData->socket = m_sockListen;
     CreateIoCompletionPort((HANDLE)m_sockListen,CompletionPort,(ULONG_PTR)perDandleData,0);

	// 开始监听  
	listen(m_sockListen,SOMAXCONN);
	

	
	SOCKADDR_IN local,client;
	
	int iaddrSize = sizeof(SOCKADDR_IN);
	
	
	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;
	
	
	//注意:
	//想要使用重叠I/O的话，初始化Socket的时候一定要使用WSASocket并带上WSA_FLAG_OVERLAPPED参数才可以(只有在服务器端需要这么做，在客户端是不需要的)
	

	LPFN_ACCEPTEX     m_lpfnAcceptEx = NULL;         // AcceptEx函数指针  
    GUID GuidAcceptEx = WSAID_ACCEPTEX;        // GUID，这个是识别AcceptEx函数必须的  
	DWORD dwBytes = 0;    
  
	if( WSAIoctl(  
		m_sockListen,   
		SIO_GET_EXTENSION_FUNCTION_POINTER,   
		&GuidAcceptEx,   
		sizeof(GuidAcceptEx),   
		&m_lpfnAcceptEx,   
		sizeof(m_lpfnAcceptEx),   
		&dwBytes,   
		NULL,   
		NULL) == 0 )
	{
		cout<<"WSAIoctl success..."<<endl;
	}
	else
	{
		cout<<"WSAIoctl failed..."<<endl;
         switch(WSAGetLastError())
         {
         case WSAENETDOWN:
             cout<<""<<endl;
             break;
         case WSAEFAULT:
             cout<<"WSAEFAULT"<<endl;
             break;
         case WSAEINVAL:
             cout<<"WSAEINVAL"<<endl;
             break;
         case WSAEINPROGRESS:
             cout<<"WSAEINPROGRESS"<<endl;
             break;
         case WSAENOTSOCK:
             cout<<"WSAENOTSOCK"<<endl;
             break;
         case WSAEOPNOTSUPP:
             cout<<"WSAEOPNOTSUPP"<<endl;
             break;
         case WSA_IO_PENDING:
             cout<<"WSA_IO_PENDING"<<endl;
             break;
         case WSAEWOULDBLOCK:
             cout<<"WSAEWOULDBLOCK"<<endl;
             break;
         case WSAENOPROTOOPT:
             cout<<"WSAENOPROTOOPT"<<endl;
             break;
         }
         return 0;
	}

	
	//准备调用 AcceptEx 函数，该函数使用重叠结构并于完成端口连接
    LPPER_IO_OPERATION_DATA perIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR,sizeof(PER_IO_OPERATION_DATA));
	memset(&(perIoData->OperationType),0,sizeof(OVERLAPPED));    
    perIoData->OperationType = ACCEPT;
    //在使用AcceptEx前需要事先重建一个套接字用于其第二个参数。这样目的是节省时间
    //通常可以创建一个套接字库
	perIoData->sockAccept = WSASocket(AF_IPX, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	perIoData->NumberOfBytesRecvd = MSGSIZE;
    DWORD flags = 0;

	//调用AcceptEx函数，地址长度需要在原有的上面加上16个字节
    //注意这里使用了重叠模型，该函数的完成将在与完成端口关联的工作线程中处理
	cout<<"Process AcceptEx function wait for client connect..."<<endl;

	int rc = m_lpfnAcceptEx(//AcceptEx的函数指针
		m_sockListen,//服务器应用程序在这个套接字上等待连接。
		perIoData->sockAccept,//将用于连接的套接字。此套接字必须不能已经绑定或者已经连接。
		perIoData->szMessage,//指向一个缓冲区，该缓冲区用于接收新建连接的所发送数据的第一个块、该服务器的本地地址和客户端的远程地址。接收到的数据将被写入到缓冲区0偏移处，而地址随后写入。 该参数必须指定，如果此参数设置为NULL，将不会得到执行，也无法通过GetAcceptExSockaddrs函数获得本地或远程的地址。
		perIoData->NumberOfBytesRecvd - ((sizeof(SOCKADDR_IN)+16)*2),//指定接收数据缓冲区lpOutputBuffer的大小。这一大小应不包括服务器的本地地址的大小或客户端的远程地址，他们被追加到输出缓冲区。如果dwReceiveDataLength是零，AcceptEx将不等待接收任何数据，而是尽快建立连接。
		sizeof(SOCKADDR_IN) + 16,//为本地地址信息保留的字节数。此值必须比所用传输协议的最大地址大小长16个字节。
		sizeof(SOCKADDR_IN) + 16,//为远程地址的信息保留的字节数。此值必须比所用传输协议的最大地址大小长16个字节。 该值不能为0。
		&dwBytes,//指向一个DWORD用于标识接收到的字节数。此参数只有在同步模式下有意义。如果函数返回ERROR_IO_PENDING并在迟些时候完成操作，那么这个DWORD没有意义，这时你必须获得从完成通知机制中读取操作字节数。
		&(perIoData->overlap)//一个OVERLAPPED结构，用于处理请求。此参数必须指定，它不能为空。
		);
	if(rc == FALSE)
    {
        if(WSAGetLastError()!=ERROR_IO_PENDING)
            cout<<"lpfnAcceptEx failed.."<<endl;
    }
	int exit;
	cin>>exit;

	//向每个工作者线程都发一个特殊的完成数据包。指示每个线程都"立即结束并退出"
	//PostQueuedCompletionStatus(CompletionPort,0xFFFFFFFF,0,NULL);
	//关闭完成端口对象
	//CloseHandle(CompletionPort);
	closesocket(m_sockListen);
	WSACleanup();
	return 0;
}


DWORD WINAPI WorkerThread(LPVOID lpParam)
{
	HANDLE CompletionPort = (HANDLE)lpParam;//完成端口
	DWORD dwBytesTransferred;
	SOCKET sClient;
	LPPER_HANDLE_DATA perHandleData = NULL;////单句柄数据
	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;//单IO数据
	DWORD Flags;
	int ret;
	DWORD RecvBytes;
	while(TRUE)
	{
		//取得本次I/O的相关信息
		GetQueuedCompletionStatus(//接收调用的结果 获取排队完成状态函数
			CompletionPort,//IOCP 对应于在上面等待的完成端口
			&dwBytesTransferred,//收到数据大小 完成一次io操作后(WSASend或WSARecv) 接收实际传输的字节数
			(LPDWORD)&perHandleData,//发送数据socket 原先传递进入CreateIoCompletionPort函数的套接字返回"单据并数". 大家最好将套接字句柄保存在这个"键"中
			(LPOVERLAPPED*)&lpPerIOData,//用于接收完成的IO操作重叠结果,这实际是一个相当重要的参数,因为要用它获取每个IO操作的数据
			INFINITE//用于指定调用者希望等待一个完成数据包在完成端口上出现的事件。假如将其设为INFINITE 调用会无休止等下去
			);

		 //先检查在套接字上是否发生错误
         //当发生错误时关闭套接字同时释放掉所有的内存.
		int i = 0;

		
		if( dwBytesTransferred == 0 && (lpPerIOData->OperationType == RECV || lpPerIOData->OperationType == SEND) )
		{
			
			closesocket(perHandleData->socket);//关闭套接字sClient
			GlobalFree(perHandleData);
			GlobalFree(lpPerIOData);
			cout<<"closesocket and globalfree perhandledata periodata!"<<endl;
			continue;
		}
			
		//这是AcceptEx函数处理完成，在下面处理
		if(lpPerIOData->OperationType == ACCEPT)     //处理连接操作
        {
			 //使用GetAcceptExSockaddrs函数 获得具体的各个地址参数.
             if(setsockopt( lpPerIOData->sockAccept, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,  
                 ( char* )&(perHandleData->socket ), sizeof( perHandleData->socket ) )==SOCKET_ERROR)
                 cout<<"setsockopt..."<<endl;

             perHandleData->socket = lpPerIOData->sockAccept;

             //memcpy(&(perHandleData->clientAddr),raddr,sizeof(raddr));
             //将新的客户套接字与完成端口连接
             CreateIoCompletionPort((HANDLE)perHandleData->socket,
                 CompletionPort,(ULONG_PTR)perHandleData,0);

             memset(&(lpPerIOData->overlap),0,sizeof(OVERLAPPED));
             lpPerIOData->OperationType = RECV;         //将状态设置成接收
             //设置WSABUF结构
             lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
			 lpPerIOData->Buffer.len = MSGSIZE;

             cout<<"wait for data arrive(Accept)..."<<endl;
             Flags = 0;
             if(WSARecv(perHandleData->socket,&(lpPerIOData->Buffer),1,
                 &RecvBytes,&Flags,&(lpPerIOData->overlap),NULL)==SOCKET_ERROR)
			 {
				 if(WSAGetLastError()==WSA_IO_PENDING)
				 {
					 cout<<"WSARecv Pending..."<<endl;
				 }
                     
			 } 
             continue;
		}

		if(lpPerIOData->OperationType == RECV)
            cout<<lpPerIOData->Buffer.buf<<endl;//将接收到的数据显示出来
			Flags = 0;
			lpPerIOData->OperationType = RECV;//设置成接受数据类型

			ZeroMemory(&(lpPerIOData->OperationType),sizeof(OVERLAPPED));
			//重新投递一个新的接收请求
			cout<<" wait for data arrive..."<<endl;
			WSARecv(
				perHandleData->socket,
				&(lpPerIOData->Buffer),
				1,
				&RecvBytes,
				&Flags,
				&(lpPerIOData->overlap),
				NULL
				);
			
		
	}

	return 0;
}
*/

//
//#define SEND 0
//#define RECV 1
//#define ACCEPT 2
//
//#define DATA_LENGTH 1000
////单句柄数据定义
//typedef struct _PER_HANDLE_DATA
//{
//     SOCKET socket;     //相关的套接字
//     SOCKADDR_STORAGE clientAddr;     //客户端的地址
//}PER_HANDLE_DATA,*LPPER_HANDLE_DATA;
//
////但IO操作数据
//typedef struct{
//     OVERLAPPED overlapped;
//     WSABUF buffer;     //一个数据缓冲区,用于WSASend/WSARecv中的第二个参数
//     char dataBuffer[DATA_LENGTH];     //实际的数据缓冲区
//     int dataLength;                     //实际的数据缓冲区长度
//     int operatorType;                 //操作类型,可以为SEND/RECV两种
//     SOCKET client;                     //分别表示发送的字节数和接收的字节数
//}PER_IO_DATA,*LPPER_IO_DATA;
//
//DWORD WINAPI ServerThread(LPVOID);
//
//void main()
//{
//     HANDLE CompletionPort;
//     WSADATA data;
//     SYSTEM_INFO info;
//     SOCKADDR_IN addr;
//     SOCKET Listen;
//
//     unsigned int i;
//     WSAStartup(MAKEWORD(2,2),&data);
//
//     //创建一个IO完成端口
//     CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
//     //确定处理器的数量
//     GetSystemInfo(&info);     //创建线城
//     for(i=0;i<info.dwNumberOfProcessors * 2;i++)
//     {
//         //根据处理器的数量创建相应多的处理线程
//         HANDLE thread = CreateThread(NULL,0,ServerThread,CompletionPort,0,NULL);
//         CloseHandle(thread);
//     }
//     //创建一个监听套接字(进行重叠操作)
//     Listen = WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
//     //将监听套接字与完成端口绑定
//     LPPER_HANDLE_DATA perDandleData;
//     perDandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR,sizeof(PER_HANDLE_DATA));
//     perDandleData->socket = Listen;
//     CreateIoCompletionPort((HANDLE)Listen,CompletionPort,(ULONG_PTR)perDandleData,0);
//
//     addr.sin_family = AF_INET;
//     addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     addr.sin_port = htons(5500);
//
//     bind(Listen,(PSOCKADDR)&addr,sizeof(addr));
//     listen(Listen,5);
//
//     LPFN_ACCEPTEX lpfnAcceptEx = NULL;     //AcceptEx函数指针
//     //Accept function GUID
//     GUID guidAcceptEx = WSAID_ACCEPTEX;
//     //get acceptex function pointer
//     DWORD dwBytes = 0;
//     if(WSAIoctl(Listen,SIO_GET_EXTENSION_FUNCTION_POINTER,
//         &guidAcceptEx,sizeof(guidAcceptEx),&lpfnAcceptEx,sizeof(lpfnAcceptEx),
//         &dwBytes,NULL,NULL)==0)
//         cout<<"WSAIoctl success..."<<endl;
//     else{
//         cout<<"WSAIoctl failed..."<<endl;
//         switch(WSAGetLastError())
//         {
//         case WSAENETDOWN:
//             cout<<""<<endl;
//             break;
//         case WSAEFAULT:
//             cout<<"WSAEFAULT"<<endl;
//             break;
//         case WSAEINVAL:
//             cout<<"WSAEINVAL"<<endl;
//             break;
//         case WSAEINPROGRESS:
//             cout<<"WSAEINPROGRESS"<<endl;
//             break;
//         case WSAENOTSOCK:
//             cout<<"WSAENOTSOCK"<<endl;
//             break;
//         case WSAEOPNOTSUPP:
//             cout<<"WSAEOPNOTSUPP"<<endl;
//             break;
//         case WSA_IO_PENDING:
//             cout<<"WSA_IO_PENDING"<<endl;
//             break;
//         case WSAEWOULDBLOCK:
//             cout<<"WSAEWOULDBLOCK"<<endl;
//             break;
//         case WSAENOPROTOOPT:
//             cout<<"WSAENOPROTOOPT"<<endl;
//             break;
//         }
//         return;
//     }
//
//     //while(true)
//     //{
//         //准备调用 AcceptEx 函数，该函数使用重叠结构并于完成端口连接
//         LPPER_IO_DATA perIoData = (LPPER_IO_DATA)GlobalAlloc(GPTR,sizeof(PER_IO_DATA));
//         memset(&(perIoData->overlapped),0,sizeof(OVERLAPPED));    
//         perIoData->operatorType = ACCEPT;
//         //在使用AcceptEx前需要事先重建一个套接字用于其第二个参数。这样目的是节省时间
//         //通常可以创建一个套接字库
//         perIoData->client = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED);
//
//         perIoData->dataLength = DATA_LENGTH;
//         DWORD flags = 0;
//        
//         //调用AcceptEx函数，地址长度需要在原有的上面加上16个字节
//         //注意这里使用了重叠模型，该函数的完成将在与完成端口关联的工作线程中处理
//         cout<<"Process AcceptEx function wait for client connect..."<<endl;
//         int rc = lpfnAcceptEx(Listen,perIoData->client,perIoData->dataBuffer,
//             perIoData->dataLength-((sizeof(SOCKADDR_IN)+16)*2),
//             sizeof(SOCKADDR_IN)+16,sizeof(SOCKADDR_IN)+16,&dwBytes,
//             &(perIoData->overlapped));
//         if(rc == FALSE)
//         {
//             if(WSAGetLastError()!=ERROR_IO_PENDING)
//                 cout<<"lpfnAcceptEx failed.."<<endl;
//         }
//
//         cin>>i;
//     closesocket(Listen);
//     WSACleanup();
//}

//DWORD WINAPI ServerThread(LPVOID lpParam)
//{
//     HANDLE CompletionPort = (HANDLE)lpParam;
//     DWORD bytes;
//     LPPER_HANDLE_DATA perHandleData = NULL;     //单句柄数据
//     LPPER_IO_DATA perIoData;             //单IO数据
//     DWORD Flags;
//     int ret;
//     DWORD RecvBytes;
//     //进入循环的等待重叠操作的完成
//     while(true)
//     {
//         bytes = -1;
//         ret=GetQueuedCompletionStatus(
//             CompletionPort,                 //原先的完成端口句柄
//             &bytes,                         //重叠操作完成的字节数
//             (LPDWORD)&perHandleData,     //原先和完成端口句柄关联起来的单句柄数据
//             (LPOVERLAPPED*)&perIoData,     //用于接收已完成的IO操作的重叠结构
//             INFINITE);                     //在完成端口上等待的时间 INFINITE 为无限等待
//        
//         //先检查在套接字上是否发生错误
//         //当发生错误时关闭套接字同时释放掉所有的内存.
//         int i = 0;
//         if(bytes == 0 && (perIoData->operatorType == RECV ||
//             perIoData->operatorType == SEND))
//         {
//             closesocket(perHandleData->socket);
//             GlobalFree(perHandleData);
//             GlobalFree(perIoData);
//             cout<<"closesocket and globalfree perhandledata periodata!"<<endl;
//             continue;
//         }
//         //这是AcceptEx函数处理完成，在下面处理
//         if(perIoData->operatorType == ACCEPT)     //处理连接操作
//         {
//             //使用GetAcceptExSockaddrs函数 获得具体的各个地址参数.
//             if(setsockopt( perIoData->client, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,  
//                 ( char* )&(perHandleData->socket ), sizeof( perHandleData->socket ) )==SOCKET_ERROR)
//                 cout<<"setsockopt..."<<endl;
//
//             perHandleData->socket = perIoData->client;
//
//             //memcpy(&(perHandleData->clientAddr),raddr,sizeof(raddr));
//             //将新的客户套接字与完成端口连接
//             CreateIoCompletionPort((HANDLE)perHandleData->socket,
//                 CompletionPort,(ULONG_PTR)perHandleData,0);
//
//             memset(&(perIoData->overlapped),0,sizeof(OVERLAPPED));
//             perIoData->operatorType = RECV;         //将状态设置成接收
//             //设置WSABUF结构
//             perIoData->buffer.buf = perIoData->dataBuffer;
//             perIoData->buffer.len = perIoData->dataLength = DATA_LENGTH;
//
//             cout<<"wait for data arrive(Accept)..."<<endl;
//             Flags = 0;
//             if(WSARecv(perHandleData->socket,&(perIoData->buffer),1,
//                 &RecvBytes,&Flags,&(perIoData->overlapped),NULL)==SOCKET_ERROR)
//                 if(WSAGetLastError()==WSA_IO_PENDING)
//                     cout<<"WSARecv Pending..."<<endl;
//             continue;            
//         }
//         if(perIoData->operatorType == RECV)
//             cout<<perIoData->buffer.buf<<endl;     //将接收到的数据显示出来
//         Flags = 0;
//         perIoData->operatorType = RECV;             //设置成接受数据类型
//
//         ZeroMemory(&(perIoData->overlapped),sizeof(OVERLAPPED));
//         //重新投递一个新的接收请求
//         cout<<" wait for data arrive..."<<endl;
//         WSARecv(perHandleData->socket,&(perIoData->buffer),1,
//             &RecvBytes,&Flags,&(perIoData->overlapped),NULL);
//     } 
//
//     return 0;
//}
//





//class D
//{ 
//public: 
//    D()  {    cout<<"D"<<endl;   } 
//    ~D() {    cout<<"~D"<<endl;   } 
//public:
//	int d;
//}; 
//class A 
//{ 
//public: 
//	A()  {    cout<<"A = "<<_d.d<<endl;    } 
//    ~A() {    cout<<"~A"<<endl;   }
//	virtual void Test(){cout<<"Atest"<<endl;};//父类=子类  父类调用子类重写父类的函数 实现多态
//	//void Test(){cout<<"Atest"<<endl;};//无virtual时候 父类=子类  即便父类调用子类重写父类的函数  仍然是调用父类函数
//	/*
//	virtual实现多态实例
//	情景:(A是B的父类 fun是父类一个虚函数 子类重写)
//	有virtual:
//	A *a = new B()
//	a->fun();//此时这个函数是调用了子类的函数 
//	无virtual:
//	A *a = new B()
//	a->fun();//此时这个函数是调用了父类的函数 
//	*/
//private:
//	D _d;
//}; 
// class C
//{ 
//public: 
//    C()  {    cout<<"C"<<endl;    } 
//    ~C() {    cout<<"~C"<<endl;   }
//}; 
//class B:public A 
//{ 
//public: 
//	B()
//    { 
//        cout<<"B"<<endl; 
//    } 
//    ~B() 
//    { 
//        cout<<"~B"<<endl; 
//    } 
//	void Test(){cout<<"Btest"<<endl;};
//private:
//	C _c;
//}; 
//int GetSecend(int *arr,int sum);
//int main(void) 
//{ 
//	B *b = new B();
//    //A *a = new A();
//	//A a;
//	cout<<"!!!!!!!!!!!!!!!!!!!!!"<<endl;
//    //B *b = new B();
//	b->Test();
//	cout<<"====================="<<endl;
//	delete(b);
//	//delete(a);
//	//a = NULL;
//	b = NULL;
//	cout<<"******************"<<endl;
//	char a[4];
//	int arr[] = {2,3,50,5,100,7};
//	cout<<sizeof(a)<<endl;
//	cout << "in main..." << endl;
//    cout << "array address: " << arr << endl;
//    cout << "array size: " << sizeof(arr) << endl;
//    cout << "array element count: " << sizeof(arr) / sizeof(arr[0]) << endl;
//	
//	//cout<<strlen(a)<<endl;
//	cout<<"GetSecend = "<< GetSecend(arr,sizeof(arr) / sizeof(arr[0])) <<endl;
//	system("pause");
//    return 0;
//} 
////找出第二大的数
//int GetSecend(int arr[],int sum)
//{
//	if(sum < 2)
//		return 0;
//	else if(sum == 2)
//		return arr[0]>arr[1]?arr[1] : arr[0];
//
//	int max,second;
//	if (arr[0]>arr[1])
//	{
//		max = arr[0];
//		second = arr[1];
//	}
//	else
//	{
//		max = arr[1];
//		second = arr[0];
//	}
//	
//
//	for (int i = 2; i < sum; i++)
//	{
//		if(max > arr[i] && arr[i] > second)
//		{
//			second = arr[i];
//		}
//		else if(arr[i] > max)
//		{
//			second = max;
//			max = arr[i];
//		}
//	}
//	
//
//	return second;
//
//}


//class D
//{ 
//public: 
//    D()  {    cout<<"D"<<endl;   } 
//    ~D() {    cout<<"~D"<<endl;   } 
//public:
//	int d;
//}; 
//class A 
//{ 
//public: 
//	A()  {    cout<<"A = "<<_d.d<<endl;    } 
//    ~A() {    cout<<"~A"<<endl;   }
//	virtual void Test(){cout<<"Atest"<<endl;};//父类=子类  父类调用子类重写父类的函数 实现多态
//	//void Test(){cout<<"Atest"<<endl;};//无virtual时候 父类=子类  即便父类调用子类重写父类的函数  仍然是调用父类函数
//	/*
//	virtual实现多态实例
//	情景:(A是B的父类 fun是父类一个虚函数 子类重写)
//	有virtual:
//	A *a = new B()
//	a->fun();//此时这个函数是调用了子类的函数 
//	无virtual:
//	A *a = new B()
//	a->fun();//此时这个函数是调用了父类的函数 
//	*/
//private:
//	D _d;
//}; 
// class C
//{ 
//public: 
//    C()  {    cout<<"C"<<endl;    } 
//    ~C() {    cout<<"~C"<<endl;   }
//}; 
//class B:public A 
//{ 
//public: 
//	B()
//    { 
//        cout<<"B"<<endl; 
//    } 
//    ~B() 
//    { 
//        cout<<"~B"<<endl; 
//    } 
//	void Test(){cout<<"Btest"<<endl;};
//private:
//	C _c;
//}; 
//int GetSecend(int *arr,int sum);
//int main(void) 
//{ 
//	B *b = new B();
//    //A *a = new A();
//	//A a;
//	cout<<"!!!!!!!!!!!!!!!!!!!!!"<<endl;
//    //B *b = new B();
//	b->Test();
//	cout<<"====================="<<endl;
//	delete(b);
//	//delete(a);
//	//a = NULL;
//	b = NULL;
//	cout<<"******************"<<endl;
//	char a[4];
//	int arr[] = {2,3,50,5,100,7};
//	cout<<sizeof(a)<<endl;
//	cout << "in main..." << endl;
//    cout << "array address: " << arr << endl;
//    cout << "array size: " << sizeof(arr) << endl;
//    cout << "array element count: " << sizeof(arr) / sizeof(arr[0]) << endl;
//	
//	//cout<<strlen(a)<<endl;
//	cout<<"GetSecend = "<< GetSecend(arr,sizeof(arr) / sizeof(arr[0])) <<endl;
//	system("pause");
//    return 0;
//} 
////找出第二大的数
//int GetSecend(int arr[],int sum)
//{
//	if(sum < 2)
//		return 0;
//	else if(sum == 2)
//		return arr[0]>arr[1]?arr[1] : arr[0];
//
//	int max,second;
//	if (arr[0]>arr[1])
//	{
//		max = arr[0];
//		second = arr[1];
//	}
//	else
//	{
//		max = arr[1];
//		second = arr[0];
//	}
//	
//
//	for (int i = 2; i < sum; i++)
//	{
//		if(max > arr[i] && arr[i] > second)
//		{
//			second = arr[i];
//		}
//		else if(arr[i] > max)
//		{
//			second = max;
//			max = arr[i];
//		}
//	}
//	
//
//	return second;
//
//}

