#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *command = NULL;
	size_t bufsize = 0;
	printf("$ ");

	if (getline(&command, &bufsize, stdin) == -1)
	{
		perror("Error reading command");
		exit(EXIT_FAILURE);
	}
	printf("You entered: %s", command);
	free(command);
	return 0;
}
