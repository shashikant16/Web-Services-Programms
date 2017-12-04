#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main( int argc, char *argv[] ) {
	int sockfd, newsockfd, portno, clilen,cnt =0;
   	char buffer[256];
   	struct sockaddr_in serv_addr, cli_addr;
   	int  n;
   
   	/* First call to socket() function */
   	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   	if (sockfd < 0) {
      		perror("ERROR opening socket");
      		exit(1);
   	}
   
   	/* Initialize socket structure */
   	bzero((char *) &serv_addr, sizeof(serv_addr));
   	portno = 5003;
   
   	serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = INADDR_ANY;
   	serv_addr.sin_port = htons(portno);
   	
   	/* Now bind the host address using bind() call.*/
   	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
   	   perror("ERROR on binding");
   	   exit(1);
   	}
   	   
   	/* Now start listening for the clients, here process will
   	   * go in sleep mode and will wait for the incoming connection
   	*/
   		
   	listen(sockfd,5);
   	clilen = sizeof(cli_addr);
   	//while(1)
	//{
   		/* Accept actual connection from the client */
   		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		
		if (newsockfd < 0) {
      			perror("ERROR on accept");
      			exit(1);
   		}
   
   		/* If connection is established then start communicating */
   		
		while(cnt == 0)
		{
			bzero(buffer,256);
   			n = read( newsockfd,buffer,255 );
   	
   			if (n < 0) {
   			   perror("ERROR reading from socket");
   			   exit(1);
   			}
   	
   			printf("Client: %s",buffer);
   			if(buffer[0] == 'b' && buffer[1] == 'y' && buffer[2] == 'e')
			{
				cnt = 1;
			}
   			/* Write a response to the client */
			bzero(buffer,256);
			printf("Server : ");
			fgets(buffer,255,stdin);
   			n = write(newsockfd,buffer,255);
   			printf("\n");
   			if (n < 0) {
   			   perror("ERROR writing to socket");
   			   exit(1);
   			}
   		}   
		close(newsockfd);
		close(sockfd);
   		exit(1);
		return 0;
	//}
}		
	
