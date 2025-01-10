#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

extern char **environ;

int print_env(char **args)
{
	int i;

	if (args[1] != NULL)
	{
		fprintf(stderr, "env: too many arguments\n");
		return (1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return (0);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[2];

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(EXIT_FAILURE);
		}

		line[strcspn(line, "\n")] = 0;
		args[0] = line;

		if (strcmp(args[0], "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			print_env(args);
		}
		else
		{
			if (fork() == 0)
			{
				execve(args[0], args, environ);
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
			wait(NULL);
		}
	}

	free(line);
	return (0);
}

