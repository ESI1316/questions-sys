#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_1 0
#define SEM_2 1

void operation(int sem, int sem_num, int op)
{
	struct sembuf s = {sem_num, op, 0};
	semop(sem, &s, 1);
}
void up(int sem, int sem_num)
{
	operation(sem, sem_num, 1);
}
void down(int sem, int sem_num)
{
	operation(sem, sem_num, -1);
}

void quit(int s)
{
	if (s == SIGINT)
		exit(EXIT_SUCCESS);
}

int main()
{
	signal(SIGINT, SIG_IGN);
	int set = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
	semctl(set, SEM_1, SETVAL, 1);
	semctl(set, SEM_2, SETVAL, 0);

	if (fork() == 0)
	{
		signal(SIGINT, quit);
		for(;;)
		{
			down(set, SEM_1);
			fprintf(stdout, "La poule ");
			fflush(stdout);
			sleep(1);
			up(set, SEM_2);
		}

	}
	if (fork() == 0)
	{
		signal(SIGINT, quit);
		for(;;)
		{
			down(set, SEM_2);
			fprintf(stdout, "pond un oeuf, youpie. \n");
			fflush(stdout);
			sleep(1);
			up(set, SEM_1);
		}
	}

	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	semctl(set, SEM_1, IPC_RMID);
}
