#define _XOPEN_SOURCE

#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <wait.h>

#define SEM_UN 0
#define SEM_DEUX 1

void exit_error(char * message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void display_msg(char * message)
{
	for (int i = 0; i < 10; ++i)
	{
		printf("%s", message);
		sleep(1);
	}
}

int main()
{

	int pid1, pid2, sem;

	if ((sem = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666)) == -1)
		exit_error("Erreur semget");

	if (semctl(sem, SEM_UN, SETVAL, 0) == -1)
		exit_error("erreur semctl 0");

	if (semctl(sem, SEM_DEUX, SETVAL, 0) == -1)
		exit_error("erreur semctl 1");

	struct sembuf up;
	struct sembuf down;

	up.sem_op = 1;
	up.sem_flg = 0;

	down.sem_op = -1;
	down.sem_flg = 0;


	pid1 = fork();
	if (pid1 == 0)
	{
		display_msg("Process 1\n");

		up.sem_num = SEM_UN;
		semop(sem, &up, 1);
		exit(EXIT_SUCCESS);
	}
	else if (pid1 == -1)
	{
		exit_error("Erreur fork pid1");
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			display_msg("Process 2\n");
			up.sem_num = SEM_DEUX;
			semop(sem, &up, 1);
			exit(EXIT_SUCCESS);
		}
		else if (pid2 == -1)
		{
			exit_error("Erreur fork pid2");
		}
		else
		{
			down.sem_num = SEM_UN;
			semop(sem, &down, 1);

			down.sem_num = SEM_DEUX;
			semop(sem, &down, 1);

			display_msg("Process 3\n");

			while (waitpid(-1, NULL, WNOHANG) > 0);

			if ( semctl(sem, SEM_UN, IPC_RMID) == -1)
				exit_error("Delete set sem");
		}
	}

	exit(EXIT_SUCCESS);
}


