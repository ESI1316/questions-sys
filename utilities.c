#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

bool isDigit(char * string, size_t size)
{
	bool is = true;
	int cpt = 0;

	while (is && cpt < size)
	{
		is = (isdigit(string[cpt]) != 0);
		cpt++;
	}

	return isDigit;
}


int main()
{
	if(isDigit("Enculé", 6))
	if(isDigit("12", 2))
	if(isDigit("l2", 2))
	if(isDigit("1l", 2))
	if(isDigit("123", 3))

	exit(EXIT_SUCCESS);
}
