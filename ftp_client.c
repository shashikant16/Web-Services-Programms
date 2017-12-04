#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
int main()
{
	int sockfd;
	char fname[25];
	int i, len;
	struct sockaddr_in servaddr,cliaddr;
	char c, buffer[256], ipadd[20];
	FILE *f;
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		printf("Error in creating socket\n");
		exit(0);
	}
	bzero(&servaddr,sizeof(servaddr));
	
	printf("Enter the IP address of the server ");
	scanf("%s",ipadd);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(ipadd);
	servaddr.sin_port=htons(12345);
	//inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	
	connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
	f=fopen("add.txt","r");
	i=0;
	
	do
	{
		c=fgetc(f);
		buffer[i++] = c;	
	}while(c!=EOF);
	buffer[i]='\0';
	write(sockfd,buffer,strlen(buffer));
	printf("The file was sent successfully\n");
	fclose(f);
}
