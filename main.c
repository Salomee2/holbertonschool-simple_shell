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
	char *cmd_path;
	char *token;
	char *args[100];
	int i;

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

		i = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		cmd_path = find_command_in_path(args[0]);
		if (cmd_path)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(cmd_path, args, NULL) == -1)
				{
					perror(args[0]);
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
			printf("./hsh: 1: %s: not found\n", args[0]);
		}
	}

	free(line);
	return (0);
}

