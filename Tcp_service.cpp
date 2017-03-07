#include <WINSOCK2.H>
#include <stdio.h>
#include <stdlib.h> 
#pragma comment(lib,"ws2_32.lib")
//int  main()
//{
//	//�����׽���
//	WORD myVersionRequest;
//	WSADATA wsaData;
//	myVersionRequest=MAKEWORD(1,1);
//	int err;
//	err=WSAStartup(myVersionRequest,&wsaData);
//	if (!err)
//	{
//		printf("�Ѵ��׽���\n");
//	} 
//	else
//	{
//		//��һ�����׽���
//		printf("Ƕ����δ��!");
//		return 0;
//	}
//	SOCKET serSocket=socket(AF_INET,SOCK_STREAM,0);//�����˿�ʶ���׽���
//	//��Ҫ�󶨵Ĳ���
//	SOCKADDR_IN addr;
//	addr.sin_family=AF_INET;
//	addr.sin_addr.S_un.S_addr=inet_addr("192.168.10.58");//htonl(INADDR_ANY);//ip��ַ
//	addr.sin_port=htons(60000);//�󶨶˿�
//
//	bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));//�����
//	listen(serSocket,5);//���еڶ������������ܹ����յ�����������
//
//	//////////////////////////////////////////////////////////////////////////
//	//��ʼ���м���
//	//////////////////////////////////////////////////////////////////////////
//	SOCKADDR_IN clientsocket;
//	int len=sizeof(SOCKADDR);
//	while (1)
//	{
//		SOCKET serConn=accept(serSocket,(SOCKADDR*)&clientsocket,&len);//������ﲻ��accept����conection�Ļ������ͻ᲻�ϵļ���
//		char sendBuf[100];
//
//		sprintf(sendBuf,"welcome %s to bejing",inet_ntoa(clientsocket.sin_addr));//�ҶԶ�Ӧ��IP���ҽ������ִ�ӡ������
//		send(serConn,sendBuf,strlen(sendBuf)+1,0);
//		char receiveBuf[100];//����
//		recv(serConn,receiveBuf,strlen(receiveBuf)+1,0);
//		printf("%s\n",receiveBuf);		
//		closesocket(serConn);//�ر�
//	}	
//	WSACleanup();//�ͷ���Դ�Ĳ���
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

	//�������ڼ������׽���  
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);  

	SOCKADDR_IN addrSrv;  
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(port); //1024���ϵĶ˿ں�  
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
		//�ȴ��ͻ�������    
		SOCKET sockConn = accept(sockSrv, (SOCKADDR *) &addrClient, &len);  
		if(sockConn == SOCKET_ERROR){  
			printf("Accept failed:%d", WSAGetLastError());  
			break;  
		}  

		printf("Accept client IP:[%s]\n", inet_ntoa(addrClient.sin_addr));  


		char recvBuf[100];  
		memset(recvBuf, 0, sizeof(recvBuf));  
		//      //��������  
		recv(sockConn, recvBuf, sizeof(recvBuf), 0);  
		printf("%d���յ����ݣ�%s\n",i, recvBuf);  


		//��������  
		int iSend = send(sockConn, buf, sizeof(buf) , 0);  
		if(iSend == SOCKET_ERROR)
		{  
			printf("send failed\n");  
			break;  
		} 
		printf("%d���͵����ݣ�%s\n",i,buf);
		closesocket(sockConn);  
		i++;
	}  

	closesocket(sockSrv);  
	WSACleanup();  
	system("pause");  
}