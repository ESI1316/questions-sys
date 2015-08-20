#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char * argv[])
{
	int sock;
	struct sockaddr_in server;
	struct hostent * hp;
	//int mySock;
	char buffer[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
	{
		fprintf(stderr, "Erreur création de socket");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	//server.sin_addr.s_addr = INADDR_ANY;
	
	hp = gethostbyname(argv[1]);
	if (hp == NULL)
	{
		fprintf(stderr, "Erreur hostbyname");
	close(sock);
		exit(EXIT_FAILURE);
	}

	memcpy(&server.sin_addr, hp->h_addr_list[0], hp->h_length);
	server.sin_port = htons(5500);

	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
	{
		fprintf(stderr, "Erreur connection");
	close(sock);
		exit(EXIT_FAILURE);
	}

	char data[] = "hello world";
	if(send(sock, data, sizeof(data), 0) < 0)
	{
		fprintf(stderr, "Erreur send");
	close(sock);
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Message : %s", data);
	close(sock);

	return 0;
}

