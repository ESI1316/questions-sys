/* Question PRe, page 4 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>



int main()
{
	if(fork() == 0)
	{
		fprintf(stdout, "execl  : \n");
		execl("/bin/ls", "ls", NULL); 
		// l == arguments sont varargs NULL terminé.
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
	if(fork() == 0)
	{
		fprintf(stdout, "execv  : \n");
		char * args[] = {"ls", NULL};
		execv("/bin/ls", args); 
		// v == arguments sont tab NULL terminé.
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
	if(fork() == 0)
	{
		fprintf(stdout, "execlp : \n");
		execlp("ls", "ls", NULL); 
		// p == executable et nom chemin
		// /!\ si un fichier binaire 'ls' se
		// trouve dans le dossier courant
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
	if(fork() == 0)
	{
		fprintf(stdout, "execvp : \n");
		char * args[] = {"ls", NULL};
		execvp("ls", args);
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);
	if(fork() == 0)
	{
		fprintf(stdout, "execlpe execlve avec variable d'env.   : \n");
		/*
		   char * args[] = {"ls", NULL};
		   char * argv[] = {};
		   execlpe("/bin/ls", "ls", NULL);
		   execvpe("/bin/ls", args);
		   */
		exit(EXIT_SUCCESS);
	}
	waitpid(-1, NULL, 0);

	exit(EXIT_SUCCESS);
}
