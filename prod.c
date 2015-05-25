#define _XOPEN_SOURCE

#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

#define QUANTITY 10 // Nombre maximum de ressources
#define SEM_PROD 0 // id du semaphore producteur dans le set de sémaphores
#define SEM_CONS 1 // id du semaphore consommateur dans le set de sémaphores
#define INC 1 // Incrémentation
#define DEC -1 // Décrémentation

/**
 * Structure partagée en mémoire, indice de la tête du tableau, indice de la
 * queue du tableau et le tableau partagé
 */
typedef struct shared {
	int head;
	int queue;
	char produits[QUANTITY];
	int remaining;
} shared;

/**
 * Termine le processus et écrit dans la bonne sortie selon le status.
 */
void exit_on(char * message, int status)
{
	if (status == EXIT_FAILURE)
		perror(message);
	else
		printf("%s \n", message);

	exit(status);
}

/** 
 * Effectue une operation sur :
 * le set de sémaphore sem,
 * au semaphore numéro sem_n,
 * l'opération op
 */
void sem_op(int sem, int sem_n, int op)
{
	struct sembuf operations;
	operations.sem_num = sem_n;
	operations.sem_op = op;
	operations.sem_flg = 0;

	semop(sem, &operations, 1);
}

/**
 * Incrémente la disponibilité de : 
 * un set de semaphores sem,
 * au semaphore sem_n
 */
void up(int sem, int sem_n)
{
	sem_op(sem, sem_n, INC);
}

/**
 * Décrémente la disponibilité de : 
 * un set de semaphores sem,
 * au semaphore sem_n
 */
void down(int sem, int sem_n)
{
	sem_op(sem, sem_n, DEC);
}

/**
 * Incrémente le sémaphore producteur du set sem
 */
void up_empty(int sem)
{
	up(sem, SEM_PROD);
}

/**
 * Décrémente le sémaphore producteur du set sem
 */
void down_empty(int sem)
{
	down(sem, SEM_PROD);
}

/**
 * Incrémente le sémaphore producteur du set sem
 */
void up_consommable(int sem)
{
	up(sem, SEM_CONS);
}

/**
 * Décrémente le semaphore consommateur du set sem.
 */
void down_consommable(int sem)
{
	down(sem, SEM_CONS);
}

/*
 * Besoin d'un dessin ?
 */
void exit_error(char * message)
{
	exit_on(message, EXIT_FAILURE);
}

/*
 * Besoin d'un dessin ?
 */
void exit_success(char * message)
{
	exit_on(message, EXIT_SUCCESS);
}

int main()
{
	int memId = -1; 	// Id pour la mémoire partagée.
	int semSet = -1; 	// Id du set de sémaphore partagé.
	shared * data = NULL; 	// Zone mémoire partagée.

	/**
	 * - Création d'un set de deux sémaphores
	 * - Initialisation du premier sémaphore appellé SEM_PROD avec QUANTITY
	 *   ressources disponibles.
	 * - Initialisation du second sémaphore appellé SEM_CONS avec 0 ressources
	 *   disponibles.
	 */
	//if ((semSet = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666)) == -1)
	if ((semSet = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666)) == -1)
		exit_error("semget error");
	if (semctl(semSet, SEM_PROD, SETVAL, QUANTITY) == -1)
		exit_error("semctl prod");
	if (semctl(semSet, SEM_CONS, SETVAL, 0) == -1)
		exit_error("semctl cons");
	if (semctl(semSet, 2, SETVAL, 1) == -1)
		exit_error("semctl remaining");

	/**
	 * - Création d'une zone mémoire pour une structure shared
	 * - Attachement de la mémoire partagée fraichement créée.
	 */
	if ((memId = shmget(IPC_PRIVATE, sizeof(shared), IPC_CREAT | 0666)) == -1)
		exit_error("shmget error");
	if ((data = (shared *) shmat(memId, NULL, 0666)) == (void *) -1)
		exit_error("shmat error");

	// Initialisation de la structure partagée
	data->head 	= 0; 
	data->queue = 0;
	data->produits[data->head] = '\0';
	data->remaining = 10;

	if(fork() == 0)
	{
		//for(int i = 0; i < QUANTITY; i++)
		while(1)
		{
			down(semSet, 2);
			if (data->remaining > 0)
			{
				down_consommable(semSet); // Y a t il au moins un consommable ?
				printf("Fils %d : Char : %c \n",getpid(), data->produits[data->head]);
				data->head = (data->head+ 1) % QUANTITY;
				data->remaining--;
				up_empty(semSet); // Y'a une case vide en plus maintenant.
				up(semSet, 2);
			}
			else
			{
				up(semSet, 2);
				break;
			}
		}

		if (shmdt(data) == -1) // Détachement de la zone mémoire partagée (FILS)
			exit_error("shmdt error");

		exit_success("End of forked process");
	}

	if(fork() == 0) // FILS CONSOMMATEUR
	{
		//for(int i = 0; i < QUANTITY; i++)
		while(1)
		{
			down(semSet, 2);
			if (data->remaining > 0)
			{
				down_consommable(semSet); // Y a t il au moins un consommable ?
				printf("Fils %d : Char : %c \n",getpid(), data->produits[data->head]);
				data->head = (data->head+ 1) % QUANTITY;
				data->remaining--;
				up_empty(semSet); // Y'a une case vide en plus maintenant.
				up(semSet, 2);
				sleep(1);
			}
			else
			{
				up(semSet, 2);
				break;
			}
		}

		if (shmdt(data) == -1) // Détachement de la zone mémoire partagée (FILS)
			exit_error("shmdt error");

		exit_success("End of forked process");
	}

	for(int i = 0; i < QUANTITY; i++)
	{
		down_empty(semSet); // Y a  t il une case vide à remplir ? 
		data->produits[data->queue] = 'a' + i;
		data->queue = (data->queue + 1) % QUANTITY;
		up_consommable(semSet); // Voila c'est rempli !
		sleep(1);
	}

	while (wait(NULL) > 0);

	if (shmdt(data) == -1) // Detachement de la zone mémoire (PERE)
		exit_error("shmdt error");

	if (shmctl(memId, IPC_RMID, 0) == -1) // Suppression de la zone mémoire.
		exit_error("shmctl rm data");

	if (semctl(semSet, SEM_PROD, IPC_RMID, 0) == -1) // Suppression du SET de semaphores
		exit_error("semctl rm prod");

	exit_success("End of father process");
}
