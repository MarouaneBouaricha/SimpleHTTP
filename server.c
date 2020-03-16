#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080


void setHttpHeader(char httpHeader[])
{
	char *filename = "index.html";
	if( access( filename, F_OK) != -1 ) {
    	if (access( filename, R_OK) != -1 )
    	{
		    FILE *htmlData = fopen(filename, "r");
		    char line[100];
		    char responseData[8000];
		    while (fgets(line, 100, htmlData) != 0) {
		        strcat(responseData, line);
		    }	
		    strcat(httpHeader, "HTTP/1.1 200 OK\r\n\n");
		    strcat(httpHeader, responseData);
    	}
    	else {
    		strcat(httpHeader,"HTTP/1.1 403 Forbidden\r\n\n");	
    	}
	} else {
	    strcat(httpHeader,"HTTP/1.1 404 Not Found\r\n\n");
	}
    
}


int main(int argc, char const *argv[])
{
	int server_fd, clientSocket; long valread;
	struct sockaddr_in address;

	int addrlen = sizeof(address);

	char httpHeader[8000] = {0};

	//creating the socket
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("failed creating the Socket");
		exit(EXIT_FAILURE);
	}

	//initializing the struct in memory with 0s
	memset((char*)&address, '0', sizeof(address));
	
	//filling the neccessery fields
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//assigning a port to the IP
	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("faild to Bind");
		exit(EXIT_FAILURE);
	}

	//listening for incoming connections
	if(listen(server_fd, 3) < 0)
	{
		perror("faild in listening");
		exit(EXIT_FAILURE);
	}

	setHttpHeader(httpHeader);

	while(1)
	{
		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		//creating a new socket for exchange messages when a client comes 
		if((clientSocket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
		{
			perror("faild to accept");
			exit(EXIT_FAILURE);
		}

        send(clientSocket, httpHeader, sizeof(httpHeader), 0);
        close(clientSocket);
	}

	return 0;
}