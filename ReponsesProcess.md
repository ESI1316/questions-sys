# Process

## Questions principales

* Un processus effectue un fork(). Quel est le rôle de la table des
  interruptions, de la table des processus, de l'ordonnanceur, de l'OS dans ce
  cas ?

* wait(), wait4() : Quelle est l'utiité ? Arguments ? Valeur de retour ?

* Définir un zombie, son utilité, les problèms que cela génère, comment les
  créer et comment les détruire

* execve(), execl, execv, execlp : Quelle est l'utilité ? Arguments ? Valeur de
  retour ?  Quel est le rôle de la table des interruptions, 
  de la table des processus, de l'ordonnanceur, de l'OS dans ce cas ?

## Questions secondaires

* (fork) Quelle est la conséquence pour une variable x définie avant le fork() ?
  Que vaut &x ?

* (fork) Quelle est la conséquence pour une lecture dans un ficheir qui a été
  ouvert avant le fork() ?

* (fork) fork() dans une boucle : Que se passe-t-il si la boucle est un 
  for(i = 0; i < 3; i++)
