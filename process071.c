#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int j;

	if (fork() == 0)
	{
		execlp("mkdir", "mkdir", "rep", NULL);
	}

	wait(&j); // wait for mkdir to finish

	if ((j == 0) && (fork() == 0)) // check if mkdir was successful and touch the file
	{
		execlp("touch", "touch", "rep/file", NULL);
	}

	wait(0); // wait for touch

	if (fork() == 0) // execute ls in all case
	{
		execlp("ls", "ls", "-l", "rep/file", NULL);
	}

	wait(0); // wait for ls

	exit(0);
}
