/*=========================================================================
  �������ƣ�	ex02_UDPEchoServer
  ����ļ���	ex02_UDPEchoServer .c
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

static unsigned short port = 8000;

int main(int argc, char *argv[])
{
	int recvNum = 0;
	char *recvBuffer = (char *)malloc(4002);
	int recvLen;
	int listenfd, connfd;
	struct sockaddr_in serverAddr, clientAddr;

	printf("TCP Echo Server Started\n");
	// Create a UDP socket connection
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);				//�����׽���
	if(listenfd == -1)
	{
		printf("Invalid socket\n");
		exit(1);
	}
	//�׽��ֵ�ַ��ֵ
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	printf("Binding server socket to port %d\n", port);
	//Ϊ����Э���ַ��һ���׽ӿ�
	if(bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr)) == -1)
	{
		printf("Bad bind\n");
		exit(1);
	}
	for(;;)
	{
		ssize_t len;
		socklen_t clientAddrLen = sizeof(clientAddr);
		// waiting for data
		printf("(%03d)================================\n", recvNum++);
		printf("Waiting for data...\n");
		len = recvfrom(listenfd, recvBuffer, 4000, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
		recvBuffer[len] = '\0';
		printf("Received: %s\n", recvBuffer);
		sendto(listenfd, recvBuffer, len, 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
		if(strcmp(recvBuffer, "exit") == 0)
			break;
	}
	close(connfd);
	exit(0);
}
