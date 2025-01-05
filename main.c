#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include <string.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf ("($) ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}
		line[strcspn(line, "\n")] = '\0';
		execute_command(line);
	}

	free(line);
	return (0);
}
