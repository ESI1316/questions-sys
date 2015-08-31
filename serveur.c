#define _BSD_SOURCE
#define _XOPEN_SOURCE

#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

void handler_int(int sig)
{
	fprintf(stdout, "Vous avez quittez le serveur. \n");
	exit(EXIT_SUCCESS);
}

void handler_kill(int sig)
{
	fprintf(stdout, "Mort du sous-serveur. \n");
	waitpid(-1, NULL, WNOHANG);
}

void exitOnError(const char * message)
{
	fprintf(stderr,"%s \n", message);
	exit(EXIT_FAILURE);
}

int main()
{
	signal(SIGINT, handler_int);
	signal(SIGCHLD, handler_kill);

	int sock;
	int handle;
	int count;
	char buf[255] = "\0";
	struct sockaddr_in server;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
		exitOnError("Socket() serveur : Nok \n");
	else
		fprintf(stdout, "Socket() serveur : ok \n");  

	server.sin_family = AF_INET;
	server.sin_port = htons(5990);

	//inet_aton("127.0.0.1", (struct in_addr *) &server.sin_addr.s_addr);
	// Lorsqu'on indique INADDR_ANY lors de l'attachement, la socket sera
	// affectée à toutes les interfaces locales. Si on invoque listen(2) ou
	// connect(2) sur une socket non affectée, elle est automatiquement attachée
	// à un port libre aléatoire, avec l'adresse locale fixée sur INADDR_ANY. 
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
		exitOnError("bind() serveur : Nok \n");
	else
		fprintf(stdout, "bind() serveur : ok \n");  

	if (listen(sock, 2) < 0)
		exitOnError("listen() serveur : Nok \n");
	else
		fprintf(stdout, "listen() serveur : ok \n");  

	while((handle = accept(sock, NULL, NULL)) >= 0)
	{
		if (fork() == 0)
		{
			close(sock);
			count = read(handle, &buf, sizeof(buf));
			printf("Recu %d charactères : %s \n",count, buf);
			close(handle);
			exit(EXIT_SUCCESS);
		}

		close(handle);
	}

	close(sock);
	exit(EXIT_SUCCESS);
}
