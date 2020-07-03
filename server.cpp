#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

// SSL includes
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

int main(int argc, char const *argv[])
{
	// initializing openSSL
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

	// making file descriptor for socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// setting socket options
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
						&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// setting address and port 
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// binding file descriptor to address information 
	if (bind(server_fd, (struct sockaddr *) &address,
				sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// listening on the server for a connection
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for(;;)
	{
	// once a new connection has been made, accept 
		if ((new_socket = accept(server_fd, (struct sockaddr *) &address,
						(socklen_t*)&addrlen))<0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}

		// using read to read from the server
		valread = read(new_socket, buffer, 1024);
		printf("%s\n", buffer);
		send(new_socket, hello, strlen(hello), 0);
		printf("Hello message sent \n");
	}
	return 0;
}
