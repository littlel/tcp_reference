#include <WinSock2.h>  
#include <stdio.h>  
#pragma comment(lib, "ws2_32.lib")  


void main()  
{  
	//加载套接字  
	WSADATA wsaData;  
	char buff[1024];  
	memset(buff, 0, sizeof(buff));  

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)  
	{  
		printf("Failed to load Winsock");  
		return;  
	}  

	SOCKADDR_IN addrSrv;  
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(60000);  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.10.58");  

	//创建套接字  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);  
	if(SOCKET_ERROR == sockClient){  
		printf("Socket() error:%d", WSAGetLastError());  
		return;  
	}  

	//向服务器发出连接请求  
	if(connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET){  
		printf("Connect failed:%d", WSAGetLastError());  
		return;  
	}
	else  
	{  
		//发送数据  
		char buff[] = "hello, this is a Client....";  
		send(sockClient, buff, sizeof(buff), 0);  
		printf("发送的内容：%",buff);

		char recvbuff[1024]={0};
		//接收数据  
		recv(sockClient, recvbuff, sizeof(recvbuff), 0);  
		printf("接收的内容：%s\n", recvbuff);  
	}  

	//关闭套接字  
	closesocket(sockClient);  
	WSACleanup();  
	system("pause");
}  