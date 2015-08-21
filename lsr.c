#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>

/* Pas totalement fonctionnel 
 * A l'air de boucler lorsqu'on indique "/" en path de dÃ©part
 */

int tree(char * argv, int level) {

	struct dirent * dirp;
	DIR * dp;
	struct stat stats;
	char path[PATH_MAX];
	char savePath[PATH_MAX];
	dp = opendir(argv);

	strcpy(savePath, argv);
	strcpy(path, argv);

	dirp = readdir(dp);
	while (dirp != NULL) {

		if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0) {
			strcpy(path, savePath);
			strcat(path, "/");
			strcat(path, dirp->d_name);

			if (stat(path, &stats) == 0) {	
				if (S_ISDIR(stats.st_mode)) {		
					int j;
					for (j = 0; j < level; j++)
						printf("  ");
					printf("%s\n", dirp->d_name);
					tree(path, level + 1); // path est pas juste , il faut mettre l'ancien path.

				} else if (S_ISREG(stats.st_mode)) {
					int j;
					for(j = 0; j < level; j++)
						printf("  ");
					printf("%s\n", dirp->d_name);
				}
				// else if fichier, afficher fichier !
			}
		}
		dirp = readdir(dp);
	}
	closedir(dp);

	return 0;


}



int main (int argc, char *argv[]) {

	if (argc != 2)  {
		perror("MTree usage : ./Mtree dir");
		exit(1);
	} else {
		return tree(argv[1], 1);
	}


}

