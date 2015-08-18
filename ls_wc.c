#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
	int p[2];

	pipe(p);

	if (fork() == 0)
	{
		close(p[0]);
		dup2(p[1], 1);

		execl("/bin/ls", "ls", NULL);
	}

	if (fork() == 0)
	{
		close(p[1]);
		dup2(p[0], 0);

		execl("/usr/bin/wc", "wc", "-l", NULL);
	}

	close(p[0]);
	close(p[1]);

	wait(NULL);
	waitpid(-1, NULL, 0);
	while (waitpid(-1, NULL, WNOHANG) > 0);
	exit(EXIT_SUCCESS);
}
