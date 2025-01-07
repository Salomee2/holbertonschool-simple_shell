#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main - entry point
 * Return: nothing
 */

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	int n_char;
	char *token;
	char **array;
	int status, i = 0;
	pid_t pid;

	array = malloc(sizeof(char *) * 1024);
	while (1)
	{
		write(1, "$ ", 2);
		n_char = getline(&buffer, &buffer_size, stdin);
		token = strtok(buffer, "\t\n");
		while (token)
		{
			array[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}
		array[i] = NULL;
		pid = fork();
		if (pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
				perror("execve");
		}
		else
			wait(&status);
		i = 0;
		free(array);
	}
}
