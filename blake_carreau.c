#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <wait.h>

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

int tokenize(char * buffer, char * tokens[], const char * delimiter)
{
	int i = 0;
	tokens[i] = strtok(buffer, delimiter);

	while (tokens[i] != NULL) tokens[++i] = strtok(NULL, delimiter);

	return i;
}

int main()
{
	//  mkdir rep && cd rep; touch f; pwd

	char buffer[BUFFER_T] = "\0";
	char * tokens[TOKENS_T];
	int nb_tokens = 0;

	prompt(buffer);
	nb_tokens = tokenize(buffer, tokens, " \n\t");

	while(strncmp(buffer, "exit", sizeof("exit") - 1) != 0)
	{
		if (tokens[0] != NULL && strncmp(tokens[0], "mkdir", sizeof("mkdir") -1) == 0)
		{
			if (tokens[1] != NULL) 
			{
				if (fork() == 0)
					execlp(tokens[0], tokens[0], tokens[1], NULL);
				waitpid(-1, NULL, 0);
			}

			if(tokens[2] != NULL && strncmp(tokens[2], "&&", sizeof("&&") - 1))
			{
				if(tokens[3] != NULL & strncmp(tokens[3], "cd", sizeof("cd") - 1))
				{
					if(tokens[4] != NULL)
					{
						if (chdir(tokens[4]) == -1)
							exit_error("Erreur de changement de dossier");
					}
				}
			}

		}
		else if (tokens[0] != NULL && strncmp(tokens[0], "touch", sizeof("touch") -1) == 0)
		{
			if(tokens[1] != NULL)
			{
				if (fork() == 0)
					if(execlp(tokens[0], tokens[0], tokens[1], NULL))
						exit_error("Erreur touch");
				waitpid(-1, NULL, 0);
			}
		}
		else if (tokens[0] != NULL && strncmp(tokens[0], "pwd", sizeof("pwd") -1) == 0)
		{
			char * cd = getcwd(NULL, 0);

			if(cd != NULL)
			{
				fprintf(stdout, "%s\n", cd);
				free(cd);
			}
		}
		else
		{
			if(fork() == 0)
				if (execvp(tokens[0], tokens) == -1)
					exit_error("Commande invalide");
			waitpid(-1, NULL, 0);
		}


		prompt(buffer);
		nb_tokens = tokenize(buffer, tokens, " \n\t");
	}
	exit(EXIT_SUCCESS);
}
