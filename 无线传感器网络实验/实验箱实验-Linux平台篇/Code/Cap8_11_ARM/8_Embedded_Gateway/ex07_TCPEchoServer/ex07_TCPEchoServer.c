/*=========================================================================
  工程名称：	ex02_TCPEchoServer
  组成文件：	ex02_TCPEchoServer .c
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

static unsigned short port = 8000;				//定义端口号为8000

int main(int argc, char *argv[])
{
	char *recvBuffer = (char *)malloc(4002);	//非配数据接收内存
	int recvLen;
	int listenfd, connfd;
	struct sockaddr_in serverAddr, clientAddr;
	int clientAddrSize;

	printf("TCP Echo Server Started\n");

	// Create a TCP socket connection
	listenfd = socket(AF_INET, SOCK_STREAM, 0);		//将套接口由主动转为被动
	if(listenfd == -1)
	{
		printf("Invalid socket\n");
		exit(1);
	}
	//socket地址赋值
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	printf("Binding server socket to port %d\n", port);
	//为本地协议地址绑定socket端口
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
		//阻塞等待客户端的连接
		connfd = accept(listenfd, (struct sockaddr *)&clientAddr, &clientAddrSize);
		if(connfd == -1)
		{
			printf("Bad accept\n");
			exit(1);
		}
		//接收PC机发来的数据并发送回去
		while((recvLen = recv(connfd, recvBuffer, 4000, 0)) > 0)
		{
			send(connfd, recvBuffer, recvLen, 0);
		}
		printf("Connection closed.\n");
		close(connfd);
	}
	return 0;
}
