# IPC 

## Questions principales 

### Expliquez le mécanisme du producteur-consommateur. Détaillez-en le principe, le code, les appels système liés.

### Expliquez la réalisation d'une section critique via "variable partagée", "blocage des interruptions" et via "sémaphores de Dijkstra". Détaillez les appels système Down et Up. Comparrez ces trois approches.

### Expliquez la réalisation d'une section critique via "BTS", "alternance" et via "sémaphores de Deijkstra". Détaillez les appels système Down et up. Comparez ces trois approches.


### semget(), semctl(), semop() : Quelle est l'utilité ? Quels sont les arguments ? Quelle est la valeur de retour ? Etablissez le lien entre ces appels système et ceux vus en théorie (up() et down())

### lc | wc -l : Comment l'OS parvient à exécuter cette ligne de commande ? Expliquez en détail le mécanisme sous-jacent. De façon très détaillée, expliquez comment il parvient à synchroniser wc et ls afin que wc ait toujours des données à lire.

### Quels appels système permettent de gérer les signaux ? Détaillez-en les paramètres et le fonctionnement. Quelles sont les limites et les défauts de ces signaux ? Quel est le rôle de la table des interruptions, de la table des processus, de l'ordonnanceur dans ces cas ?

### socket(), bind(), listen(), accept(), connect() : Quelle est l'utilité ? Quels sont les arguments ? Quelle est la valeur de retour ? 

### Utilisation de l'appel système pipe et situations d'interblocages : expliquez en vous basant sur des exemples de code comment une telle situation peut être obtenue. Détaillez et faites le lien avec les appels système Up et Down.

## Questions secondaires

### (socket) Quelle est l'utilité de la fonction htons() ? Comment faire parvenir un message à un processus qui s'exécute sur un autre ordinateur ? 

### (socket) Comment écrire une application client / serveur où plusieurs clients peuvent être connectés au serveur en même temps ? 




