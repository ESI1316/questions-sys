/** Ecrire un programme qui simule l'utilisation de trap :
 * attention, il s'agit d'une fonction du bash comme cd (voir man bash)
 * Utilisation : 
 * trap - 	: Remet tous les signaux à leur place
 * trap function sig_num : assigne une fonction à un signal
 *
 * voir :
 * man 7 signal pour les signaux
 */

#define _XOPEN_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <signal.h>

#define NB_SIG 32
#define BUFFER_S 256
#define TOKENS_S 100

typedef void (*sighandler_t)(int);

char * signals[NB_SIG];

/**
 * Cette fonction nettoie le tableau de chaine dynamique.
 */
void clean()
{
	for (int i = 0; i < NB_SIG; i++)
		if (signals[i] != NULL)
		{
			free(signals[i]);
			signals[i] = NULL;
		}
}

/**
 * Sortie en erreur avec message
 */
void exit_error(char * message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

/**
 *
 */
void kill_children(int sig)
{
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

/**
 * Fonction associée à un signal : celle-ci lancera la commande stockée dans le
 * tableau de commande "signals".
 *
 * La fonction fait un fork pour éffectuer la commande dans un nouveau process.
 */
void function_signal(int sig_num)
{
	if (signals[sig_num] != NULL)
	{
		if (fork() == 0)
		{
			if (execlp(signals[sig_num], signals[sig_num], NULL) == -1)
				exit_error("Erreur d'exec");
		}

		wait(NULL);
		signal(sig_num, function_signal);
		/* Contrairement  aux  systèmes  BSD,  les signaux sous Linux
		 reprennent  leurs  comportements  par  défaut  après  leur
		 première réception. Il est donc généralement nécessaire de
		 réarmer le gestionnaire (par un nouvel appel à signal ) 
		  au sein même du gestionnaire.
		 */
	}
}

/** 
 * Cette fonction reinitialise les fonctions de bases aux signaux.
 * Certains ne peuvent être modifiés, d'où le message d'avertissement.
 */
void clean_functions()
{
	clean();

	for (int i = 0; i < NB_SIG; i++)
		if (signal(i, SIG_DFL) == SIG_ERR)
			fprintf(stderr, "Attention, signal %d  ne peut être modifié\n", i);
}

/**
 *
 */
char * get_rules()
{
	return "Bad use of TRAP : \n \"trap -\" \n \"trap function sig_num[0-31]\"";
}

/**
 *
 * retourne le numéro du dernier token (NULL);
 */
int tokenize(char ** tokens, char * line, char * delimiter)
{
	int i = 0;

	tokens[i] = strtok(line, delimiter);

	while(tokens[i] != NULL)
		tokens[++i] = strtok(NULL, delimiter);

	return i;
}

void prompt(char * buffer)
{
	printf("SHELL $ ");
	fgets(buffer, BUFFER_S, stdin);
}

int main()
{
	char line[BUFFER_S + 1];
	char * tokens[TOKENS_S];

	/*
	struct sigaction action;

	action.sa_handler = kill_children;
	sigaction(SIGCHLD, &action, NULL);
	*/

	prompt(line);

	while((strcmp(line, "exit\n") != 0))
	{
		int i = tokenize(tokens, line, " \n\t");

		if ((tokens[0] != NULL) && (strcmp(tokens[0], "trap") == 0))
		{
			if ((tokens[1] != NULL) && (strcmp(tokens[1], "-") == 0))
				clean_functions();
			else if ((tokens[1] != NULL) && (tokens[2] != NULL))
			{
				int sig = atoi(tokens[2]);
				sighandler_t old = signal(sig, function_signal);

				if (old == SIG_ERR || sig < 0 || sig > 31)
				{
					fprintf(stderr, "%s \n",  get_rules());
					fflush(stderr);
				}
				else
				{
					if (signals[sig] != NULL)
					{
						free(signals[sig]);
						signals[sig] = NULL;
					}

					signals[sig] = malloc(sizeof(char) * (strlen(tokens[1]) + 1));
					strcpy(signals[sig], tokens[1]);
				}
			}
			else
			{
				fprintf(stderr, "%s \n",  get_rules());
				fflush(stderr);
			}
		}
		else
		{
			if(fork() == 0)
			{
				if(execvp(tokens[0], tokens) == -1)
					exit_error("Invalid command");
			}

			wait(NULL); // Tuer via le sigchild provoque des erreurs.
		}

		for (int j = 0; j < i; j++) tokens[j] = NULL;
		prompt(line);
	}

	clean();
	exit(EXIT_SUCCESS);
}
