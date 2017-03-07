#include <WINSOCK2.H>
#include <stdio.h>
#include <stdlib.h> 
#pragma comment(lib,"ws2_32.lib")
//int  main()
//{
//	//创建套接字
//	WORD myVersionRequest;
//	WSADATA wsaData;
//	myVersionRequest=MAKEWORD(1,1);
//	int err;
//	err=WSAStartup(myVersionRequest,&wsaData);
//	if (!err)
//	{
//		printf("已打开套接字\n");
//	} 
//	else
//	{
//		//进一步绑定套接字
//		printf("嵌套字未打开!");
//		return 0;
//	}
//	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//创建了可识别套接字
//	//需要绑定的参数
//	SOCKADDR_IN addr;
//	addr.sin_family=AF_INET;
//	addr.sin_addr.S_un.S_addr=inet_addr("192.168.10.58");//htonl(INADDR_ANY);//ip地址
//	addr.sin_port=htons(60000);//绑定端口
//
//	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//绑定完成
//	listen(serSocket,5);//其中第二个参数代表能够接收的最多的连接数
//
//	//////////////////////////////////////////////////////////////////////////
//	//开始进行监听
//	//////////////////////////////////////////////////////////////////////////
//	SOCKADDR_IN clientsocket;
//	int len=sizeof(SOCKADDR);
//	while (1)
//	{
//		SOCKET serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//如果这里不是accept而是conection的话。。就会不断的监听
//		char sendBuf[100];
//
//		sprintf(sendBuf,"welcome %s to bejing",inet_ntoa(clientsocket.sin_addr));//找对对应的IP并且将这行字打印到那里
//		send(serConn,sendBuf,strlen(sendBuf)+1,0);
//		char receiveBuf[100];//接收
//		recv(serConn,receiveBuf,strlen(receiveBuf)+1,0);
//		printf("%s\n",receiveBuf);		
//		closesocket(serConn);//关闭
//	}	
//	WSACleanup();//释放资源的操作
//	
//	return 0;
//}
void main()
{
	WSADATA wsaData;  
	int port = 60000;  
	char buf[] = "Server: hello, I am a server.....";   

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)  
	{  
		printf("Failed to load Winsock");  
		return;  
	}  

	//创建用于监听的套接字  
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);  

	SOCKADDR_IN addrSrv;  
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(port); //1024以上的端口号  
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  

	int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));  
	if(retVal == SOCKET_ERROR){  
		printf("Failed bind:%d\n", WSAGetLastError());  
		return;  
	}  

	if(listen(sockSrv,10) ==SOCKET_ERROR){  
		printf("Listen failed:%d", WSAGetLastError());  
		return;  
	}  

	SOCKADDR_IN addrClient;  
	int len = sizeof(SOCKADDR);  
	int i = 1;
	while(1)  
	{  
		//等待客户请求到来    
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *) &addrClient, &len);  
		if(sockConn == SOCKET_ERROR){  
			printf("Accept failed:%d", WSAGetLastError());  
			break;  
		}  

		printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));  


		char recvBuf[100];  
		memset(recvBuf, 0, sizeof(recvBuf));  
		//      //接收数据  
		recv(sockConn, recvBuf, sizeof(recvBuf), 0);  
		printf("%d接收的数据：%s\n",i, recvBuf);  


		//发送数据  
		int iSend = send(sockConn, buf, sizeof(buf) , 0);  
		if(iSend == SOCKET_ERROR)
		{  
			printf("send failed\n");  
			break;  
		} 
		printf("%d发送的数据：%s\n",i,buf);
		closesocket(sockConn);  
		i++;
	}  

	closesocket(sockSrv);  
	WSACleanup();  
	system("pause");  
}