#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char line[256];
	char * tokens[100];

	fprintf(stdout, "PROMPTEUR $ ");
	fgets(line, 256, stdin);

	int i = 0;
	tokens[i] = strtok(line, " \t\n");

	while(tokens[i] != NULL)
		tokens[++i] = strtok(NULL, " \t\n");

	if (tokens[0] != NULL && strcmp(tokens[0], "ls") == 0)
	{
		DIR * current = opendir(".");
		struct dirent * entry = readdir(current);

		while (entry != NULL)
		{
			fprintf(stdout, "nom = %s \n", entry->d_name);
			entry = readdir(current);
		}
		
		closedir(current);
	}

	else
	{
		if(fork() == 0)
		{
			if (execvp(tokens[0], tokens) == -1)
			{
				fprintf(stderr, "Commande invalide");
				exit(EXIT_FAILURE);
			}
		}
	}

	exit(EXIT_SUCCESS);
}


