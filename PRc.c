/* Exercice PRc page 4 */
#define _XOPEN_SOURCE

#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void sem_op(int sem, int sem_n, int op)
{
	struct sembuf operations;
	operations.sem_num = sem_n;
	operations.sem_op = op; // +1 -1
	operations.sem_flg = 0;

	semop(sem, &operations, 1);
}

int main()
{

	int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

	int memid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

	int * i = (int *) shmat(memid, NULL, 0666);
	semctl(semid, 0, SETVAL, 1);

	*i = 0;

	for(int j = 0; j < 3; j++)
	{
		if (fork() == 0){
			sem_op(semid, 0, -1);
			printf("%d :: %d \n", getpid(), *i);
			*i = *i + 1;
			sem_op(semid, 0, 1);
		}
	}

	shmdt(i);
	// semctl(semid, 0, IPC_RMID); // Erreur si détruit avant la fin
	exit(EXIT_SUCCESS);
}
