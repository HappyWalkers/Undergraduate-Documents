#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	struct sockaddr_in sockaddr;
	struct sockaddr_in sockaddr_connect;
	socklen_t socket_len = 0;
	int sockfd = -1;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{	
		perror("socket the TCP server");
		exit(EXIT_FAILURE);
	}
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(8080);
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1 )
	{
		close(sock);
		perror("bind socket");
		exit(EXIT_FAILURE);
	}

	if(listen(sock, 1) < 0)
	{
		close(sock);
		perror("list socket");
		exit(EXIT_FAILURE);
	}
	
	socket_len = sizeof(sockaddr_connect);	
	printf("accpet.......\n");
	if((sockfd = accept(sock, (struct sockaddr *)&sockaddr_connect, &socket_len))< 0)
	{
		close(sock);
		perror("accept socket");
		exit(EXIT_FAILURE);
	}
	printf("the accpet sockfd is %d\n", sockfd);
	while(1)
	{
		char recvBuf[100];
	    	memset(recvBuf, 0, sizeof(recvBuf));
	    	read(sockfd, recvBuf, sizeof(recvBuf));
	   	printf("the recvBuf is %x %x %s\n", recvBuf[0], recvBuf[1], &recvBuf[2]);
	}
	close(sockfd);
	close(sock);
	return 0;
}
