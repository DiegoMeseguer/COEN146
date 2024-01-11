//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a client that connects to a server and transfers the bytes read from a file over the established connection
//
// The input arguments are as follows:
// argv[1]: Sever's IP address
// argv[2]: Server's port number
// argv[3]: Source file
// argv[4]: Destination file at the server side which includes a copy of the source file

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define    SIZE 10

int main (int argc, char *argv[]){
	int	sockfd = 0;			// socket descriptor
	char	net_buff[SIZE];			// to hold the bytes read from socket
	char	file_buff[SIZE];		// to hold the bytes read from source file
	struct	sockaddr_in serv_addr;		// server address structure
	int	net_bytes_read;			// numer of bytes received over socket
	FILE	*source_file;			// pointer to the source file

	if (argc < 5){
		printf ("Usage: ./%s <server ip address> <server port number> <source file>  <destination file>\n", argv[0]);
		return 1;
	}
	
	int port;
	port = atoi(argv[2]);

	// Make sure intial values are zero
	memset (net_buff, '0', sizeof (net_buff));
	memset (file_buff, '0', sizeof (file_buff));
	memset (&serv_addr, '0', sizeof (serv_addr));
	
	// Create a socket
        int network_socket;
        network_socket = socket(AF_INET, SOCK_STREAM, 0);

        // Specify address for the socket
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr);

        // Call the connect() function
        int status;
        status = connect(network_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

        // Check possible error
        if (status == -1) {
                printf("Something went wrong when connecting to the socket\n");
        }

	// Send filename to server
	char buffer[11];
	int to_write, to_read;
	bzero(buffer, sizeof(buffer));
	to_write = write(network_socket, argv[4], sizeof(buffer));
	if (to_write < 0) {
		 printf("ERROR writing to socket");
	}

 	// Print response from server
	bzero(buffer, sizeof(buffer));
	to_read = read(network_socket, buffer, sizeof(buffer));
        if (to_read < 0) {
                printf("ERROR reading from socket");
        }
        printf("Here is the reply from the server: %s\n", buffer);

     	// Transfer input file of client to output file of server in chunks of 10 bytes
	FILE *s_file = fopen(argv[3], "r");
	
	while((to_read = fread(file_buff, sizeof(char), SIZE, s_file)) > 0) {

		printf("Sending %d bytes to server\n", to_read);

		for(int i = 0; i < sizeof(file_buff); i++) {
			printf("Read characters: %c\n", file_buff[i]);
		}
		printf("\n");

		to_write = write(network_socket, file_buff, to_read);
		if (to_write < 0) {
                	 printf("ERROR writing to socket");
        	}	

		printf("Message sent to server: %s\n", file_buff);
		bzero(file_buff, sizeof(file_buff));
	}

	// Receive data from the server
	//recv(network_socket, &net_buff, sizeof(net_buff), 0);
	//printf("The server sent the data: %s\n", net_buff);

	close(network_socket);	
	
	return 0;
}



