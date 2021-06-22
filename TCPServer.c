#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXLINE 4096   
#define PORT 2000
#define LISTENQ 8
int main(int argc, char **argv)
{
	int listenfd , connfd , n;
   	int i,j;
	socklen_t clilen;
	char buf[MAXLINE];
	char ptr[100];
	struct sockaddr_in cliaddr, servaddr;



	listenfd = socket (AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	 

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen (listenfd, LISTENQ);
	printf("%s\n","server running ... waiting for connections ");
	for( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);
		printf("%s\n","Received Request ...");
		while((n = recv(connfd, buf, MAXLINE, 0))>0)  {
			printf("%s","String received from and resent to the client :");
			puts(buf);
			for(i=strlen(buf)-1,j=0;i>=0;i--,j++){
				ptr[j] =buf[i];
			}
			ptr[j] = '\0';		

                	send(connfd, ptr, n, 0);
		}
		if(n < 0)  {
			perror("Read error");
			exit(1);
		}
		close(connfd);
	}
	close(listenfd);
}
