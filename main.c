#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	char *args[2];
	char *cmd_path;

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

		cmd_path = find_command_in_path(line);

		if (cmd_path)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(cmd_path, args, NULL) == -1)
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
			free(cmd_path);
		}
		else
		{
			printf("./hsh: 1: %s: not found\n", line);
		}
	}

	free(line);
	return (0);
}

