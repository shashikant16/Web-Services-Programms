#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int fd, nBytes,n;
	char buffer[1024],msg[100] = "Message received successfuly!!";
  	struct sockaddr_in serverAddr, clientAddr;
  	struct sockaddr_storage serverStorage;
  	socklen_t addr_size, client_addr_size;

  	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		perror("error in creating socket\n");
		exit(1);
	}
  	serverAddr.sin_family = AF_INET;
  	serverAddr.sin_port = htons(7891);
  	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  	//memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  	
  	if((bind(fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0))
	{
		perror("Error in binding\n");
		exit(1);
	}

  	//addr_size = sizeof serverStorage;
	bzero(buffer,1024);
     	nBytes = recvfrom(fd,buffer,1024,0,(struct sockaddr *)&serverAddr,&addr_size);
	if(nBytes < 0)
	{
		perror("error in receiving\n");
		exit(1);
	}
	printf("%d bytes received\n",nBytes);
	printf("Message received : %s",buffer);
	printf("\n");
	bzero(buffer,1024);
       	n = sendto(fd,msg,sizeof(msg),0,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	if(n < 0)
        {
                perror("error in sending\n");
                exit(1);
        }
  	return 0;
}
