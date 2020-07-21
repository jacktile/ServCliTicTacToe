/** SIMPLE SERVER 
 * Jackie - July 9, 2020
 *
 * SPECIFICATIONS:
 * Must accept clients/create player descriptors containing:
 * 	- Player's IP address 
 * 	- Player's player number (either 1 or 2)
 * 	- Players current score (initialized to 0)
 *
 * Must update each players screen with the new board 
 * Must only allow one player to submit their response at once 
 * 	- Send a greyed out board to the inactivate player
 * 	- Player currently submitting their score can only click on the boxes that have not yet been sent
 *
 * Tic-Tac toe algorithm
 * 	- Check if there are 3 vertically adjacent selections for each player 
 * 	- Check if there are 3 horizontally adjacent selections for each player
 * 	- Check diagonal selections for each player, for 3 selections 
 * 	- IF someone wins, depict their player number on the screen and end the process.
 *
 * Additional sources:
 * 	- For creating the server: https://aticleworld.com/socket-programming-in-c-using-tcpip/
 * OTHER NOTES
 *	- OOP adjusted implementation will be used later-- effectively using C with c++ compiler and stl
*/
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

// my function for measuring length of char* w/ null terminated char
#include "char_p_length_func.cpp"

#define PORTNUM 5001

short SocketCreate(void)
{
	/**
	 * Returns descriptor for a socket on port 
	 * specified by PORTNUM
	 */
	short hSocket;
	std::cout << "Create the socket\n";

	hSocket = socket(AF_INET, SOCK_STREAM, 0);
	return hSocket;
}

int BindCreatedSocket(int hSocket)
{
	/**
	 * Binds socket from the given descriptor 
	 */
	std::cout << "Bind the created socket\n";
	int iRetval=-1;
	int ClientPort = PORTNUM;
	struct sockaddr_in remote = {0};	// is this an alternative to memset?

	// internet address family structure
	remote.sin_family = AF_INET;

	// incoming interfaces
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	remote.sin_port = htons(ClientPort);
	iRetval = bind(hSocket, (struct sockaddr *) &remote, sizeof(remote));

	return iRetval;
}

int def_tic_tac_toe(int *tic_arr)
{
	/*
	 * Returns 0 if neither player wins
	 * If a player wins, their player ID number will be returned 
	 *
	 * tic_arr is array with 0, 1, 2 .. [] and other error info if needed
	 * - the size of this array is expected to be 9, no error checking
	 *
	 * Not an optimized algorithm, just implemented the first thing 
	 * come to mind
	 */

	// vertical check
	for (int j = 0; j < 3; j++)
	{
		if (tic_arr[j] == tic_arr[j+3] && tic_arr[j+3] == tic_arr[j+6] && tic_arr[j] != 0)
			return tic_arr[j];
	}

	// horizontal check
	for (int i = 0; i < 9; i = i+3)
	{
		if (tic_arr[i] == tic_arr[i+1] && tic_arr[i+1] == tic_arr[i+2] && tic_arr[i] != 0)
			return tic_arr[i];
	}
	
	// diagonal check
	if (tic_arr[0] == tic_arr[4] && tic_arr[4] == tic_arr[8] && tic_arr[0] != 0)
		return tic_arr[0];

	if (tic_arr[2] == tic_arr[4] && tic_arr[4] == tic_arr[6] && tic_arr[2] != 0) 
		return tic_arr[2];

	return -1;
}

int main()
{
	// variable dec
	int socket_desc, sock, clientLen, read_size;
	struct sockaddr_in server, client;
	char client_message[200] = {0};
	char message[100] = {0};
	const char *pMessage = "Wassap";

	// create socket 
	socket_desc = SocketCreate();
	if (socket_desc == -1)
	{
		printf("Could not create socket");
		return 1;
	}

	std::cout << "socket created\n";

	// binding and checking 
	if (BindCreatedSocket(socket_desc) < 0)
	{
		perror("bind failed");
		return 1;
	}

	std::cout << "Bind complete\n";

	listen(socket_desc, 3);

	// accepting incoming connections 

	while(1)
	{
		clientLen = sizeof(struct sockaddr_in);
		sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&clientLen);

		if (sock < 0)
		{
			perror("accept failed");
			return 1;
		}

		inet_ntop(client.sin_family,
				(&client.sin_addr),
			client_message, sizeof(client_message));

		printf("server: got connection from %s\n", client_message);

		if (!fork())
		{
			char *msg = "Content-type: text/html\r\n\r\n<!DOCTYPE html><html> <h1> Here is a message </h1> </html>";
			close(socket_desc);
			if (send(sock, msg, char_p_len(msg) , 0) == -1)	// might have an issue with this [13 and 0]
				perror("send");
			close(sock);
			exit(0);
		}

		close(sock);

	}
	return 0;
}
