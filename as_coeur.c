#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
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
	fprintf(stdout, "$ : ");
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
	char buffer[BUFFER_T] = "\0";
	char * tokens[TOKENS_T];
	int nb_tokens = 0;

	prompt(buffer);
	nb_tokens = tokenize(buffer, tokens, " \n\t");

	while(strncmp(buffer, "exit", 4) != 0)
	{
		if (tokens[0] != NULL && strncmp(tokens[0], "mkdir", sizeof("mkdir") -1 ) == 0)
		{
			if (tokens[1] != NULL)
			{
				if (mkdir(tokens[1], 0777) == -1)
					exit_error("Création de dossier impossible");

				if (tokens[2] != NULL && tokens[3] != NULL && tokens[4] != NULL
						&& strncmp(tokens[2], "&&", sizeof("&&") -1) == 0
						&& strncmp(tokens[3], "touch", sizeof("touch") - 1) == 0)
				{
					if (fork() == 0)
					{
						if (execlp(tokens[3], tokens[3], tokens[4], NULL) == -1)
							exit_error("Erreur de commande touch");
						
						exit(EXIT_SUCCESS);
					}

					waitpid(-1, NULL, 0);

					if (tokens[5] != NULL && tokens[6] != NULL  
							&& strncmp(tokens[5], "&&", sizeof("&&") -1) == 0)
					{
						int pid = fork();

						if (pid == 0)
						{
							if (execvp(tokens[6], & tokens[6]) == -1)
								exit_error("Commande invalide");

							exit(EXIT_SUCCESS);
						}

						waitpid(pid, NULL, 0);
					}
				}
			}
		}
		else if (tokens[0] != NULL)
		{
			int pid = fork();

			if (pid == 0)
			{
				if (execvp(tokens[0], tokens) == -1)
					exit_error("Commande invalide");

				exit(EXIT_SUCCESS);
			}

			waitpid(pid, NULL, 0);
		}

		prompt(buffer);
		nb_tokens = tokenize(buffer, tokens, "\t\n ");
	}

	exit(EXIT_SUCCESS);
}
