#define _POSIX_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <signal.h>
#include <sys/types.h>


void infanticide(int sg)
{
	printf("%s \n", "infanticide");
	if(sg = SIGCHLD) while(waitpid(-1, NULL, WNOHANG) > 0);
}

void prpr(int p)
{
	printf("sigint \n");
}
int main()

{
	signal(SIGCHLD, infanticide);
	signal(SIGINT, prpr);

	if(fork() == 0) {
		sleep(1);exit(0);
	}

	kill(getpid(), SIGINT);


	execlp("ls", "ls", "-l",  NULL);

	exit(EXIT_SUCCESS);
}
