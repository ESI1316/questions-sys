#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int sock;
	struct sockaddr_in server;
	int mySock;
	char buffer[1024];
	int rval;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0)
	{
		fprintf(stderr, "Erreur création de socket");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5500);

	if(bind(sock, (struct sockaddr *) &server, sizeof(server)) == -1)
	{
		fprintf(stderr, "Erreur bind de socket");
		exit(EXIT_FAILURE);
	}

	if(listen(sock, 5) == -1)
	{
		fprintf(stderr, "Erreur listen de socket");
		exit(EXIT_FAILURE);
	}

	for(;;)
	{
		mySock = accept(sock, (struct sockaddr *) 0, 0);

		if (mySock == -1)
		{
			fprintf(stderr, "Erreur listen de socket");
			exit(EXIT_FAILURE);
		}

		memset(buffer, 0, sizeof(buffer));
		if (rval = recv(mySock, buffer, sizeof(buffer), 0) < 0)
		{
			fprintf(stderr, "Erreur reception de socket");
			exit(EXIT_FAILURE);
		}
		else if (rval == 0)
			fprintf(stdout, "End of connexion");
		else
			fprintf(stdout, "Message %s", buffer);

		fprintf(stdout, "Message reçu (rval = %d)", rval);
		close(mySock);
	}

	return 0;
}

