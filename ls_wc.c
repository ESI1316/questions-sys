#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	int p[2];
	int fils[2];

	pipe(p);

	if ((fils[0] = fork()) == 0) 
	{
		close(p[0]); // Fermeture de la sortie du pipe
		dup2(p[1], 1); // L'entrée du pipe devient la sortie standard de ls

		execl("/bin/ls", "ls", NULL);
		//execlp("ls", "ls", NULL);
	}

	if ((fils[1] = fork()) == 0) 
	{
		close(p[1]); // Fermeture de l'entrée du pipe
		dup2(p[0], 0); // La sortie du pipe devient l'entrée stantdard de wc

		execl("/usr/bin/wc", "wc", "-c", NULL);
	}

	close(p[0]); // Pipe inutile 
	close(p[1]); // Pipe inutile 

	waitpid(fils[0], NULL, 0);
	waitpid(fils[1], NULL, 0);

	exit(EXIT_SUCCESS);
}
