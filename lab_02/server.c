//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a server that accepts connection from a client and copies the received bytes to a file
//
// The input arguments are as follows:
// argv[1]: Sever's port number

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
	char    message[10] = "received!";  // message to be sent to the client when the destination file name is received
	int     net_bytes_read;             // numer of bytes received over socket
	int     socket_fd = 0;              // socket descriptor
	int     connection_fd = 0;          // new connection descriptor
	struct  sockaddr_in serv_addr;      // Address format structure
	char    net_buff[1024];             // buffer to hold characters read from socket
	FILE    *dest_file;                 // pointer to the file that will include the received bytes over socket

	if (argc < 2){// Note: the name of the program is counted as an argument
		printf ("Port number not specified!\n");
		return 1;
	}

	int port;
	port = atoi(argv[1]);

	// Create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Specify address for the socket
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// Call the bind() function
	bind(network_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	// Call the listen() function
	listen(network_socket, 10);

	int client_socket;
	client_socket = accept(network_socket,(struct sockaddr *)NULL, NULL);
	
	// Receive filename from client
	char buffer[11];
	int to_read, to_write;
	bzero(buffer, sizeof(buffer));
	printf("%d\n",client_socket);
	to_read = read(client_socket, buffer, sizeof(buffer));
	
	if (to_read < 0) { 
		printf("ERROR reading from socket");
	} 
 	printf("Here is the filename from client: %s\n", buffer); 

	// Reply to client
	to_write = write(client_socket, message, sizeof(message));
        if (to_write < 0) {
                 printf("ERROR writing to socket");
        }
	
	// Open output file to write
	FILE *d_file = fopen(buffer, "w");

	// Receive data from client and write it to the output file
	bzero(buffer, sizeof(buffer));
	while((to_read = read(client_socket, buffer, sizeof(buffer))) > 0) {
		if (to_read < 0) {
                	printf("ERROR reading from socket");
        	}
		fwrite(buffer, sizeof(char), to_read, d_file);
	
		printf("Data received from client: %d\n", to_read);

	}

	close(network_socket);

	return 0;

}


