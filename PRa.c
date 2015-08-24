/* Question PRa, page 4 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int x = 3;

	if(fork() == 0)
	{
		fprintf(stdout, "Fils : Adresse : %p, contenu : %d \n", (void *) &x, x);
		x = 5;
		fprintf(stdout, "Fils : Adresse : %p, contenu : %d \n", (void *) &x, x);
		exit(EXIT_SUCCESS);
	}

	sleep(2);
	fprintf(stdout, "Pere : Adresse : %p, contenu : %d \n", (void *) &x, x);
	exit(EXIT_SUCCESS);
}
