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

static char SendBuf[] = "hello, UDP world!";
static char recvBuf[4000];
static unsigned short port = 8000;
static char ip[16] = "172.20.223.253";

int main(int argc, char *argv[])
{
    if(argc > 1)
        strncpy(ip, argv[1], 15);
	char *sendptr = SendBuf;
	int sendsize = strlen(SendBuf);
	int recvLen;
	int listenfd, connfd;
	struct sockaddr_in serverAddr, clientAddr;

	printf("UDP Client Started\n");
	// Create a UDP socket connection
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(listenfd == -1)
	{
		printf("Invalid socket\n");
		exit(1);
	}
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ip);

	ssize_t len;
	socklen_t serverAddrLen = sizeof(serverAddr);
	// write data to UDP server
	printf("writing data(%d) \"%s\" to server\n", sendsize, sendptr);
	sendto(listenfd,
			sendptr,
			sendsize,
			0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	// waiting for data
	printf("Waiting for data...\n");
	len = recvfrom(listenfd, recvBuf, 4000, 0, (struct sockaddr*)&serverAddr, &serverAddrLen);
	recvBuf[len] = '\0';
	printf("Received(%d): %s\n", len, recvBuf);
	close(connfd);
	return 0;
}
