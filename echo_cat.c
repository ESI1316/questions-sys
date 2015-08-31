#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

#define BUFFER_T 256
#define TOKENS_T 100

void exit_error(const char * message)
{
	fprintf(stderr, "%s \n", message);
	exit(EXIT_FAILURE);
}

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

int tokenize(char * line, char ** tokens, char * delimiter)
{
	int i = 0;

	tokens[i] = strtok(line, delimiter);

	while(tokens[i] != NULL) tokens[++i] = strtok(NULL, delimiter);

	return i;
}

int main()
{
	char buffer[BUFFER_T] = "\0";
	char * tokens[TOKENS_T];
	int nb_tokens = 0;

	prompt(buffer);
	nb_tokens = tokenize(buffer, tokens, " \n\t");

	while(strncmp(buffer, "exit", sizeof("exit") - 1) != 0)
	{
		if (tokens[0] != NULL && strncmp(tokens[0], "echo", sizeof("echo") - 1) == 0)
		{
			if (tokens[1] != NULL && tokens[2] != NULL && strncmp(tokens[2], "|", 1) == 0)
			{
				if (tokens[3] != NULL && strncmp(tokens[3], "cat", sizeof("cat") - 1) == 0)
				{
					int p[2];
					pipe(p);
					if(fork() == 0)
					{
						close(p[0]);
						dup2(p[1], 1);

						if (execlp(tokens[0], tokens[0], tokens[1], NULL) == -1)
							exit_error("echo error after pipe");
					}

					if(fork() == 0)
					{
						close(p[1]);
						dup2(p[0], 0);

						if (execlp(tokens[3], tokens[3], NULL) == 1)
							exit_error("cat error");
					}
					close(p[0]);
					close(p[1]);

					waitpid(-1, NULL, 0);
					waitpid(-1, NULL, 0);
				}
			}
			else
			{
				if (fork() == 0)
					if (execlp(tokens[0], tokens[0], NULL) == -1)
						exit_error("Error echo");

				waitpid(-1, NULL, 0);
			}
		}
		else
		{
			if (fork() == 0)
				if (execvp(tokens[0], tokens) == -1)
					exit_error("Command invalid");
			
			waitpid(-1, NULL, 0);
		}

		prompt(buffer);
		nb_tokens = tokenize(buffer, tokens, " \n\t");
	}

	exit(EXIT_SUCCESS);
}
