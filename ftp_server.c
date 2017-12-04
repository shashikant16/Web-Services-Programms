#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
#define LISTENQ 5
int main()
{
	int fd,sockfd,listenfd,connfd;
	pid_t childpid;
	socklen_t client;
	struct sockaddr_in servaddr,cliaddr;
	char buffer[100];
	FILE *fp;
	
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		printf("Error in creating socket\n");
		exit(0);
	}
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(12345);
	
	if((bind(listenfd,(SA*)&servaddr,sizeof(servaddr)))==-1)
	{
		printf("Error in binding the socket\n");
		exit(0);
	}
	
	if(listen(listenfd,LISTENQ)==-1)
	{
		printf("Error in listening\n");
		exit(0);
	}
	
	printf("Server is listening at port 12345 \n");
	
	client=sizeof(cliaddr);
	if((connfd=accept(listenfd,(SA*)&cliaddr,&client))==-1)
	{
		printf("Error in accepting client\n");
		exit(0);
	}
	
	read(connfd,buffer,256);
	fp=fopen("add1.txt","w");
	fputs(buffer,fp);
	printf("The file was received successfully\n");
	printf("The new file created is add1.txt\n");
	fclose(fp);
}
