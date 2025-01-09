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
	char *line = NULL;
	size_t len = 0;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		if (getline(&line, &len, stdin) == -1)
			break;
		line[strcspn(line, "\n")] = '\0';
		pid = fork();
		if (pid == 0)
		{
			char *args[2];
			args[0] = line;
			args[1] = NULL;
			if (execve(line, args, NULL) == -1)
			{
				perror("./hsh");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			perror("fork");
		}
	}
	free(line);
	return 0;
}
