#define _XOPEN_SOURCE
#define _BSD_SOURCE

#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void f(int s)
{
	printf("pere \n");
}

int main()
{
	signal(SIGINT, f);
	pause();
	exit(0);
}

