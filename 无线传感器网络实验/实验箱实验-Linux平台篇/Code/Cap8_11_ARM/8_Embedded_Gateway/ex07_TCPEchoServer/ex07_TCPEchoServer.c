/*=========================================================================
  �������ƣ�	ex02_TCPEchoServer
  ����ļ���	ex02_TCPEchoServer .c
  ���������� 	ͨ��UDPЭ�������PC�����͵����ݣ��ٷ��ͻ�PC��
  Ӳ�����ӣ�			
  ά����¼��	2011-04-13 v1.1		add by sunplus
=========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

static unsigned short port = 8000;				//����˿ں�Ϊ8000

int main(int argc, char *argv[])
{
	char *recvBuffer = (char *)malloc(4002);	//�������ݽ����ڴ�
	int recvLen;
	int listenfd, connfd;
	struct sockaddr_in serverAddr, clientAddr;
	int clientAddrSize;

	printf("TCP Echo Server Started\n");

	// Create a TCP socket connection
	listenfd = socket(AF_INET, SOCK_STREAM, 0);		//���׽ӿ�������תΪ����
	if(listenfd == -1)
	{
		printf("Invalid socket\n");
		exit(1);
	}
	//socket��ַ��ֵ
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	printf("Binding server socket to port %d\n", port);
	//Ϊ����Э���ַ��socket�˿�
	if(bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr)) == -1)
	{
		printf("Bad bind\n");
		exit(1);
	}
	if(listen(listenfd, 1) == -1)					// Allow 1 queued requests
	{
		printf("Bad listen\n");
		exit(1);
	}
	printf("Accepting connections(Max 1 connections)...\n");
	for(;;)
	{
		clientAddrSize = sizeof(struct sockaddr_in);
		//�����ȴ��ͻ��˵�����
		connfd = accept(listenfd, (struct sockaddr *)&clientAddr, &clientAddrSize);
		if(connfd == -1)
		{
			printf("Bad accept\n");
			exit(1);
		}
		//����PC�����������ݲ����ͻ�ȥ
		while((recvLen = recv(connfd, recvBuffer, 4000, 0)) > 0)
		{
			send(connfd, recvBuffer, recvLen, 0);
		}
		printf("Connection closed.\n");
		close(connfd);
	}
	return 0;
}
