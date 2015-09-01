#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <wait.h>

#define BUFFER_T 256
#define TOKENS_T 100

void prompt(char * buffer)
{
	char * cd = getcwd(NULL, 0);

	if(cd != NULL)
	{
		fprintf(stdout, "%s $ : ", cd);
		free(cd);
	}
	fgets(buffer, BUFFER_T, stdin);
}

int main()
{
	//  mkdir rep && cd rep; touch f; pwd

	char buffer[BUFFER_T] = "\0";

	prompt(buffer);

	while(strncmp(buffer, "exit", sizeof("exit") - 1) != 0)
	{
		if (strncmp(buffer, "mkdir rep && cd rep; touch f; pwd", strlen("mkdir rep && cd rep; touch f; pwd")) == 0)
		{
			int status;

			if (fork() == 0)
			{
				if (mkdir("rep", 0775) == 0)
					exit(EXIT_SUCCESS);
				else
					exit(EXIT_FAILURE);
			}

			waitpid(-1, &status, 0);

			if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
			{
				chdir("rep");
			}

			if (fork() == 0)
			{
				if (execlp("touch", "touch", "f", NULL) == -1)
					exit(EXIT_FAILURE);
			}
			waitpid(-1, NULL, 0);

			if (fork() == 0)
			{
				if (execlp("pwd", "pwd", NULL) == -1)
					exit(EXIT_FAILURE);
			}
			waitpid(-1, NULL, 0);
		}

		prompt(buffer);
	}
	exit(EXIT_SUCCESS);
}
