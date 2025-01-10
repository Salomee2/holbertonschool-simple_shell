#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *command = NULL;
	size_t bufsize = 0;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		if (getline(&command, &bufsize, stdin) == -1)
		{
			if (feof(stdin))
			{
				free(command);
				printf("\n");
				break;
			}
			perror("Error reading command");
			free(command);
			exit(EXIT_FAILURE);
		}
		command[strcspn(command, "\n")] = '\0';
		if (strlen(command) == 0)
			continue;

		pid = fork();
		if (pid == 0)
		{
			if (execlp(command, command, NULL) == -1)
				perror(command);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("Fork failed");
		}
	}

	return (0);
}

