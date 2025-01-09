#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	char *args[2];

	while (1)
	{
		printf("$ ");
		if (getline(&line, &len, stdin) == -1)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0)
			continue;
		args[0] = line;
		args[1] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(line, args, NULL) == -1)
			{
				perror(line);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
		}
	}

	free(line);
	return (0);
}

