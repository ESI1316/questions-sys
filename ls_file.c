#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_T 256

void prompt(char * buffer)
{
	printf("$ : ");
	fgets(buffer, BUFFER_T, stdin);
}

int main()
{
	char buffer[BUFFER_T];
	prompt(buffer);

	while(strcmp(buffer, "exit\n") != 0)
	{
		int handler = open("file", O_CREAT | O_WRONLY | O_TRUNC, 0666);

		if (handler == -1)
		{
			perror("woups \n");
			exit(EXIT_FAILURE);
		}

		if (fork() == 0)
		{
			dup2(handler, 1);
			close(handler);
			if (execlp("ls", "ls", NULL) == -1)
			{
				perror("exec woups \n");
				exit(EXIT_FAILURE);
			}

			printf("ls terminé \n");
			exit(EXIT_SUCCESS);
		}
		close(handler);
		waitpid(-1, NULL, 0);

		prompt(buffer);
	}

	exit(EXIT_SUCCESS);
}
