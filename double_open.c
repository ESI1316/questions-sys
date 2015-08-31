// Run and launch "lsof | grep read_only"
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int handle = open("./read_only", O_RDONLY);

	if(handle == -1)
	{
		perror("fu");
		exit(EXIT_FAILURE);
	}
	else
	{
		if(fork() == 0)
		{
			sleep(10);
			close(handle);
			exit(EXIT_SUCCESS);
		}

		waitpid(-1, NULL, 0);
		close(handle);

	}
	exit(EXIT_SUCCESS);
}
