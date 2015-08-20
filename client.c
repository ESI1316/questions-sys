#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

char message[] = "Kawabounga";

void exitOnError(const char * message)
{
    fprintf(stderr,"%s \n", message);
    exit(EXIT_FAILURE);
}

int main()
{
    int sock;
    struct sockaddr_in sockstr;
    struct in_addr adresse;

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
        exitOnError("Socket() client : Nok \n");
    else
        fprintf(stdout, "Socket() client : ok \n");

    sockstr.sin_family = AF_INET;
    sockstr.sin_port = htons(5990);

	if(inet_aton("127.0.0.1", &adresse) == 0)
        exitOnError("inet_aton() client : Nok \n");
    else
        fprintf(stdout, "inet_aton() client : ok \n");

    sockstr.sin_addr = adresse;

    if(connect(sock, (struct sockaddr *) &sockstr, sizeof(sockstr)) == -1)
        exitOnError("connect() client : Nok \n");
    else
        fprintf(stdout, "connect() client : ok \n");
    if (write(sock , message, sizeof(message)) < 0)
        exitOnError("write() client : Nok \n");
    else
        fprintf(stdout, "write() client : ok \n");

    close(sock);
    exit(0);
}
