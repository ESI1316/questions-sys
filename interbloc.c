#define _XOPEN_SOURCE
#define _BSD_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <stdio.h>


int main()
{
	int t1[2], t2[2];
	pipe(t1);
	pipe(t2);

	if (fork() == 0)
	{
		close(t1[1]);
		close(t2[0]);
		dup2(t1[0], 0); // lit dans t0
		dup2(t2[1], 1); // lit dans t0

		char c = 'f';
		read(0, &c, 1);
		write(1, &c, 1);
		printf("%c \n", c);

		exit(EXIT_SUCCESS);
	}

	if (fork() == 0)
	{
		close(t1[0]);
		close(t2[1]);
		dup2(t1[1], 1);
		dup2(t2[0], 0);

		char c = 'd';
		read(0, &c, 1);
		write(1, &c, 1);
		printf("%c \n", c);

		exit(EXIT_SUCCESS);
	}
		close(t1[0]);
		close(t1[1]);
		close(t2[0]);
		close(t2[1]);

	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);

	exit(EXIT_SUCCESS);
}
