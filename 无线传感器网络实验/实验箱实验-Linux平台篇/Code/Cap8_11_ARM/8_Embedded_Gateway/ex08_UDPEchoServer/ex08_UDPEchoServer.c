/*=========================================================================
  工程名称：	ex02_UDPEchoServer
  组成文件：	ex02_UDPEchoServer .c
  功能描述： 	通过UDP协议接收由PC机发送的数据，再发送回PC端
  硬件连接：			
  维护记录：	2011-04-13 v1.1		add by sunplus
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
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);				//创建套接字
	if(listenfd == -1)
	{
		printf("Invalid socket\n");
		exit(1);
	}
	//套接字地址赋值
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	printf("Binding server socket to port %d\n", port);
	//为本地协议地址绑定一个套接口
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
