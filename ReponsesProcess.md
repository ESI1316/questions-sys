# Process

## Questions principales

#### Un processus effectue un fork(). Quel est le rôle de la table des interruptions, de la table des processus, de l'ordonnanceur, de l'OS dans ce cas ?

+ Table des interruptions : ?
+ Table des processus : ?
+ Ordonnanceur : ?
+ OS : ?

#### wait(), wait4() : Quelle est l'utiité ? Arguments ? Valeur de retour ?

Wait(&status) appelle waitpid de cette manière :

```C
waitpid(-1, &status, NULL);
```

Ce dernier "attend la fin de n'importe lequel de ses fils".

+ wait4 : attend un fils spécifique
+ wait3 : attend n'importe lequel de ces fils
Dans les deux cas, un paramètre 
```C
struct rusage
```
peut être passé en paramètre, celui-ci est rempli des informations du fils.

\newpage

#### Définir un zombie, son utilité, les problèms que cela génère, comment les créer et comment les détruire

Un processus zombie est un processus terminé qui n'a pas été liberé par son
parent via l'appel wait.

Lors de l'appel du System Call exit d'un fils, le père doit le "release" pour
enlever son entrée dans la table des processus. Il est préférable d'attendre les
processus fils le plus rapidement possible pour chaque fork.

pour en créer il suffit de faire un process vide : 

```C
if(pid_f=fork()==0);if(pid_f=fork()==0);if(pid_f=fork()==0);if(pid_f=fork()==0); 	
// JaumainStyle quadruplette de process zombie.
```

Pour les détruire, il est possible de les attendre à un moment choisi dans le
code mais il se peut que un processus reste zombie durant ce laps de temps. Il
est donc préférable de lancer une fonction de nettoyage au trigger SIGCHLD qui
est lancé à la mort d'un fils.

```C
void infanticide(int sg)
{
	if(sg = SIGCHLD) while(waitpid(-1, NULL, WNOHANG) > 0);
}

signal(SIGCHLD, infanticide);

if(fork() == 0);
```

\newpage

#### execve(), execl, execv, execlp : Quelle est l'utilité ? Arguments ? Valeur de retour ?  Quel est le rôle de la table des interruptions, de la table des processus, de l'ordonnanceur, de l'OS dans ce cas ?

```C
execl(CHEMIN_COMMANDE, NOM_COMMANDE, argument, argument, ..., NULL);
```

```C
execv(CHEMIN_COMMANDE, NOM_COMMANDE, arguments[argument, argument, ..., NULL]);
```

```C
execlp(NOM_FICHIER_COMMANDE, argument, argument, ..., NULL);
execvp(NOM_FICHIER_COMMANDE, arguments[argument, argument, ..., NULL]);
```

Il est possible aussi d'utiliser execle, execve, execlpe, execvpe qui prennent
un tableau de variables d'environnement en plus (accompagné de sa taille).

Cette appel système appel un logiciel externe en remplacement l'intégralité de
son code, de ses données par celui appellé. Les arguments (varargs ou tableau)
nécessite le nom de la commande en premier argument qui simulera le char *
argv[] d'un processus principal.
La table des handle est préservée, la table des interruptions est préservée.
Le PID est préservé.

La valeur de retour est est \texttt{-1} et \textbf{peut être percu uniquement}
lors d'une erreur puisque dans le cas contraire le code suivant exe\* n'existe
plus.

## Questions secondaires

#### (fork) Quelle est la conséquence pour une variable x définie avant le fork() ? Que vaut &x ?

Il s'agit d'une copie donc la variable x n'est pas dans le même segment de data
que le père. Ce n'est pas la même adresse.

#### (fork) Quelle est la conséquence pour une lecture dans un ficheir qui a été ouvert avant le fork() ?

Le fichier est lu correctement puisque la table des handle est copié, par contre
le pere et le fils partage l'entrée du fichier dans la table des fichiers et
ouvert et donc l'indice de position dans le fichier est ausis partagée.

#### (fork) fork() dans une boucle : Que se passe-t-il si la boucle est un for(i = 0; i < 3; i++)
1 process => 2 process => 4 process => 8 process
mais de manière asynchrone, dans tous les cas, il y a 8 zombies à la fin de
"toutes les boucles".

