#include <WinSock2.h>  
#include <stdio.h>  
#pragma comment(lib, "ws2_32.lib")  


void main()  
{  
	//�����׽���  
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

	//�����׽���  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);  
	if(SOCKET_ERROR == sockClient){  
		printf("Socket() error:%d", WSAGetLastError());  
		return;  
	}  

	//�������������������  
	if(connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET){  
		printf("Connect failed:%d", WSAGetLastError());  
		return;  
	}
	else  
	{  
		//��������  
		char buff[] = "hello, this is a Client....";  
		send(sockClient, buff, sizeof(buff), 0);  
		printf("���͵����ݣ�%",buff);

		char recvbuff[1024]={0};
		//��������  
		recv(sockClient, recvbuff, sizeof(recvbuff), 0);  
		printf("���յ����ݣ�%s\n", recvbuff);  
	}  

	//�ر��׽���  
	closesocket(sockClient);  
	WSACleanup();  
	system("pause");
}  