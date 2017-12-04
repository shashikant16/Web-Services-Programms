#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  	int fd, portNum, nBytes,n;
  	char buffer[1024];
  	struct sockaddr_in serverAddr;
  	socklen_t addr_size;

  	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		perror("error in socket creation");
		exit(1);
	}
  	serverAddr.sin_family = AF_INET;
  	serverAddr.sin_port = htons(7891);
  	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  	//memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  	//addr_size = sizeof serverAddr;
	bzero(buffer,1024);
   	printf("Type a message to send to server:\n");
    	fgets(buffer,1024,stdin);
    	nBytes = strlen(buffer) + 1;
    
    	n = sendto(fd,buffer,nBytes,0,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	if(n < 0)
        {
                perror("error in sending");
                exit(1);
        }

	printf("Message sent successfully\n");
	bzero(buffer,1024);
        nBytes = recvfrom(fd,buffer,1024,0,NULL,NULL);
	//nBytes = recvfrom(fd,buffer,1024,0,(struct sockaddr *)&serverAddr, &addr_size);
	if(nBytes < 0)
        {
                perror("error in receiving");
                exit(1);
        }

    	printf("Response from server: %s",buffer);
	printf("\n");
  	return 0;
}
