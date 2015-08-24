/* Question PRb, page 4 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	int handle = open("read_only", O_RDONLY);
	char buffer[256] = "";

	read(handle, buffer, 4);
	fprintf(stdout, "Pere::read = %s \n", buffer);

	if(fork() == 0)
	{
		char buff[256] = "";
		read(handle, buff, 4);
		fprintf(stdout, "Fils::read = %s \n", buff);
		close(handle);
		exit(EXIT_SUCCESS);
	}

	close(handle);
	exit(EXIT_SUCCESS);
}
