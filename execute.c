#include "shell.h"
/**
 * execute_command - Executes a command xith execve
 * @command: command to execute
 */

void execute_command(char *command)
{
	char *argv[2];
	pid_t pid;
	int status;

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}

	if (pid == 0)
	{
		if (execve(command, argv, environ) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
