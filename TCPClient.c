#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define MAXLINE 4096   
#define SERV_PORT 2000

int main(int argc , char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline [MAXLINE], recvline [MAXLINE];


	if(argc !=2)  {
		perror("usage : TcpClient <IP address of the server ");
		exit(1);
	}
	

	if((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0)   {
		perror("problem in creating the socket ");
		exit(2);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(SERV_PORT);


	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) <0)  {
		perror("problem in connecting to the server");
		exit(3);
	}
	while (fgets(sendline, MAXLINE, stdin) != NULL)  {
		send(sockfd, sendline, strlen(sendline), 0);
		if(recv(sockfd , recvline , MAXLINE , 0) ==0) {
			perror("The server terminated permanturely ");
			exit(4);
		/*do {
			printf("Enter the first number : ");
			scanf("%s",line);
			send(sockfd,line,strlen(line)+1,0);
			printf("data sent %s\n",line);
			scanf("%s",line);
			send(sockfd,line,strlen(line)+1,0);
			printf("data sent %s\n",line);
                        exit(5);  
		  }*/
		}	
	        printf("result received from the server :%s");
        	fputs(recvline , stdout);
	  	
	}
	exit(0);
	

}
