/* Question PRd, page 4 
 * Création de "zombies"
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	if(fork() == 0) exit(EXIT_SUCCESS);
	if(fork() == 0) exit(EXIT_SUCCESS);
	if(fork() == 0) exit(EXIT_SUCCESS);
	if(fork() == 0) exit(EXIT_SUCCESS);
	if(fork() == 0) exit(EXIT_SUCCESS);

	sleep(2); // 5 zombies, bloquant des ressources, "ps aux | grep PRd" pour le voir.
	/*
	 * wait(NULL); == waitpid(-1, NULL, NULL); Attend n'importe quel fils
	 * wait3(status, option, rusage) == waitpid(-1, status, option) et remplis
	 * rusage d'informations [Obsolet]
	 * wait4(pid, status, option, rusage) == waitpid(pid, status, option) et
	 * remplis rusage d'informations [Obsolet]
	 *
	 * Utilisation optimale :
	 *
	 * waitpid(pid, NULL, 0); attend le process pid (retourné par fork())
	 * waitpid(-1, NULL, 0); attend n'importe quel fils
	 * waitpid(-1, NULL, WNOHANG); fait une tentative d'attende de fils, il n'y
	 * en a pas au moins un de terminé, le programme continue sinon il retourne
	 * un nombre positif.
	 *
	 * Le plus optimal étant d'assigner le signal SIGCHLD a une fonction qui
	 * détruit le fils. (voir le chapitre signal, man 7 signal)
	 */

	exit(EXIT_SUCCESS); // Si le père meurt, les fils meurent
}
