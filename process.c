#define _XOPEN_SOURCE

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h> 

void exit_error(char * message)
{
	perror(message);
	exit(1);
}

void display_msg(char * message)
{
	int i;
	for (i = 0; i < 10; ++i)
	{
		printf("%s", message);
		sleep(1);
	}
}

int main()
{

	int pid1, pid2, sem;

	if (sem = semget(IPC_PRIVATE, 2, 0666 | IPC_CREAT) == -1)
		exit_error("Erreur semget");



	if (semctl(sem, 0, SETVAL, 0) == -1)
		exit_error("erreur semctl 0");

	if (semctl(sem, 1, SETVAL, 0) == -1)
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

		up.sem_num = 0;
		semop(sem, &up, 1);
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
			up.sem_num = 1;
			semop(sem, &up, 1);
		}
		else if (pid2 == -1)
		{
			exit_error("Erreur fork pid2");
		}
		else
		{
			down.sem_num = 0;
			semop(sem, &down, 1);

			down.sem_num = 1;
			semop(sem, &down, 1);

			display_msg("Process 3\n");
		}
	}

	return 0;

}


