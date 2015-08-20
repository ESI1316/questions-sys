#define _BSD_SOURCE

#include <stdio.h>
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
    int sock,h,n;
    char buf[255] = "";
    struct sockaddr_in bd;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    bd.sin_family = AF_INET;
    bd.sin_port = htons(5990);
    inet_aton("127.0.0.1", (struct in_addr *) &bd.sin_addr.s_addr);

    bind(sock, (struct sockaddr *) &bd, sizeof(bd));
    listen(sock,1);

    h = accept(sock,NULL, NULL);

	if (h < 0)
		exitOnError("accept() serveur : Nok \n");
	else
		fprintf(stdout, "accept() serveur : ok \n");

    n = read(h,&buf,sizeof(buf));
    printf("Recu %d charactères : %s \n",n, buf);

    close(sock);
	close(h);

    exit(0);
}
