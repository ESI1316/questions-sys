#define _BSD_SOURCE

#include <stdio.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void exitOnError(const char * message)
{
	fprintf(stderr,"%s \n", message);
	exit(EXIT_FAILURE);
}

int main()
{
	int sock;
	int handle;
	int count;
	char buf[255] = "\0";
	struct sockaddr_in server;

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock < 0)
		exitOnError("Socket() serveur : Nok \n");
	else
		fprintf(stdout, "Socket() serveur : ok \n");  

	server.sin_family = AF_INET;
	server.sin_port = htons(5990);

	if (inet_aton("127.0.0.1", (struct in_addr *) &server.sin_addr.s_addr) == 0)
		exitOnError("inet_aton() serveur : Nok \n");
	else
		fprintf(stdout, "inet_aton() serveur : ok \n");  

	if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
		exitOnError("bind() serveur : Nok \n");
	else
		fprintf(stdout, "bind() serveur : ok \n");  

	if (listen(sock,1) < 0)
		exitOnError("listen() serveur : Nok \n");
	else
		fprintf(stdout, "listen() serveur : ok \n");  

	handle = accept(sock,NULL, NULL);
	if (handle < 0)
		exitOnError("accept() serveur : Nok \n");
	else
		fprintf(stdout, "accept() serveur : ok \n");

	if (fork() == 0)
	{
		count = read(handle, &buf, sizeof(buf));
		printf("Recu %d charactères : %s \n",count, buf);
		close(sock);
		close(handle);
		exit(EXIT_SUCCESS);
	}

	close(sock);
	close(handle);
	wait(NULL);

	exit(0);
}
