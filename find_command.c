#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char *find_command_in_path(char *command)
{
	char *path = getenv("PATH");
	char *dir = NULL, *full_path = NULL;
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token)
	{
		dir = token;
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			perror("malloc failed");
			free(path_copy);
			return NULL;
		}

		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

